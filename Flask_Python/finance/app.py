import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/",methods=["GET", "POST"])
@login_required
def index():

    """Show portfolio of stocks"""
    #checks if the user has historic (made transactions)
    test = db.execute("SELECT * from historic WHERE client_id = ?", session["user_id"])

    if (len(test))>0:
        # if thet have, check the historic for the transactions(buy and sell)
        # the Symbols, the averange price paid per share, sum of share of each symbol
        # and sum of the total values of shares per symbol
        table = db.execute("SELECT symbol, AVG(price) as averange_price, SUM(shares) as shares, SUM(total) as total FROM historic WHERE client_id = ?" , session["user_id"])

        # interate per each symbol and updates in the sql the latest price, total worth
        # difference between the old total worth and the updated one, that difference in %
        # and the averange price per share, as to use theses values later on.
        x = 0
        while x < len(table):

            averange_price = table[x]["averange_price"]
            price = (lookup(table[x]["symbol"])["price"])

            total_worth = (int(table[x]["shares"]) * int(lookup(table[x]["symbol"])["price"]))

            difference = total_worth - table[x]["total"]
            percentage = round((total_worth/table[x]["total"])-1 ,3)
            db.execute("UPDATE historic SET latest_price = ?, total_worth = ?, difference = ?, averange_price = ?, percentage = ? WHERE client_id = ? and symbol = ?",price, total_worth, difference, averange_price, percentage, session["user_id"], table[x]["symbol"])
            x+=1

        # re execute the select to update the table with the new values
        table = db.execute("SELECT symbol, averange_price, difference, latest_price, total_worth, percentage, SUM(shares) as shares, SUM(total) as total FROM historic WHERE client_id = ?" , session["user_id"])

        # add the sum of all total worth from all symbos from the historic
        total = db.execute("SELECT total_worth as total FROM historic WHERE client_id = ?" , session["user_id"])
        total=total[0]["total"]

        # select the user's total cash
        cash = db.execute("SELECT cash FROM users WHERE id = ?" , session["user_id"])
        cash=cash[0]["cash"]

        #find the grand total
        balance = total + cash

        # deletes from the historic the values that no longer have use
        db.execute("UPDATE historic SET total_worth = ?, difference = ?, averange_price = ?, percentage = ?",0,0,0,0)
        return render_template("index.html", table=table, cash=cash, total=total, balance=balance)
    # if the user has no historic
    else:
        # select the cash he has in his acc and show it in his historic
        cash=db.execute("SELECT cash FROM users WHERE id=?",session["user_id"])
        cash=int(cash[0]["cash"])
        total = 0
        return render_template("index.html", cash=cash, balance=cash, total=total)



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    # if the user arrived here through post
    if request.method == "POST":

        #check if symbol isn't empty
        if not request.form.get("symbol"):
            return apology("Must provide symbol", 400)
        symbol=request.form.get("symbol")

        #check if the share isn't empty
        if not request.form.get("shares"):
            return apology("Shares must not be blank", 400)

        # check if the share is a number
        try:
            int(request.form.get("shares"))+1
        except:
            return apology("Shares must be an integer", 400)

        # check if it's a integer
        if ((int(request.form.get("shares")) * 10)%10)!=0:
            return apology("Shares must be an integer", 400)

        # check if it's a positive number
        if int(request.form.get("shares")) < 1:
            return apology("Shares must be a positive number and higher than 0", 400)

        # look up if that symbol has shares in the market
        quote=lookup(symbol)

        # if none has been found, say it doesn't exist
        if quote == None:
            return apology("Symbol does not exist", 400)

        # save shares as a variable
        shares=int (request.form.get("shares"))

        # save the name, symbol and price of the share
        name=quote["name"]
        price=int(quote["price"])
        symbol=quote["symbol"]

        # find the total cost of the shares
        total_price = shares * price

        # check the user's cash
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

        # check how much money the user would have left after the transaction
        newbalance = int(cash[0]["cash"]) - total_price

        # if it's below 0, return that they don't have enough cash
        if newbalance < 0:
            return apology("not enough cash to complete purchase", 403)

        # if they have enough cash, insert this transaction in the historic
        db.execute("INSERT INTO historic (client_id, type, symbol, Price, shares, total) VALUES (?, ?, ?, ?, ?, ?)", session["user_id"],"buy", symbol, price, shares, total_price)

        # and update the user's cash
        db.execute("UPDATE users Set cash = ? WHERE  id = ?", newbalance, session["user_id"])

        # return the name, price/share, symbol, cash the user had before
        # transaction, total price and their new balance
        return render_template("bought.html", name=name, price=price, symbol=symbol, cash=cash[0]["cash"], total_price=total_price,newbalance=newbalance)

    # if the user arrived through get, return the buy page
    if request.method == "GET":
        return render_template("buy.html")
    return apology("TODO")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # select from historic the types of transactions, symbols, price
    # shares, total and time of transaction
    table = db.execute("SELECT type, symbol, Price, shares, total, timeOftransaction FROM historic WHERE client_id = ?" , session["user_id"])

    # return the page with theses informations
    return render_template("history.html", table=table)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # if the user arrived here through post
    if request.method == "POST":

        # check if the symbol isn't empty
        if not request.form.get("symbol"):
            return apology("Must provide symbol", 400)

        # save the symbol
        symbol=request.form.get("symbol")

        # check the info on that symbol
        quote=lookup(symbol)

        # if there isn't a symbol like it
        if quote == None:
            return apology("Symbol does not exist", 400)

        #if there is, save name, price and symbol as variables
        name=quote["name"]

        price=quote["price"]

        symbol=quote["symbol"]

        #return render_template("quoted.html", name=name, price=price, symbol=symbol)
        return render_template("quoted.html", quote=quote,name=name, price=price, symbol=symbol)

    # if the user arrived through get, show them the quote page
    if request.method == "GET":
        return render_template("quote.html")




@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    #User reached here by submited their username and password from this same page
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # check if username already exists
        if len(rows) != 0:
            return apology("Username is alrady taken", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must repeate password", 400)
        # Ensure both passwords matches
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords do not match", 400)

        #If all went well, hash the password
        password = generate_password_hash(request.form.get("password"))

        #than add it and the username to the database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", request.form.get("username"), password)
        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    if request.method == "GET":
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # if the user arrived here through post
    if request.method == "POST":

        #if symbol is empty
        if not request.form.get("symbol"):
            return apology("Must provide symbol", 400)

        # save the symbol as a variable
        symbol=request.form.get("symbol")

        # if shares is empty
        if not request.form.get("shares"):
            return apology("Shares must not be blank", 400)

        # try to check if shares is a number
        try:
            int(request.form.get("shares"))+1
        except:
            return apology("Shares must be an integer", 400)

        # check if shares is a integer
        if ((int(request.form.get("shares")) * 10)%10)!=0:
            return apology("Shares must be an integer", 400)

        # check if shares is a number above zero
        if int(request.form.get("shares")) < 1:
            return apology("Shares must be a positive number higher than 0", 400)

        # look up the symbol
        quote=lookup(symbol)

        # if there is no such symbol in database
        if quote == None:
            return apology("Symbol does not exist", 400)

        # makes sure shares is considered a int, not a str
        shares=int (request.form.get("shares"))

        # Select symbol, make and select the averange prices per share,
        # the total number of shares and the total price paid for them
        table = db.execute("SELECT symbol, AVG(price) as averange_price, SUM(shares) as shares, SUM(total) as total FROM historic WHERE client_id = ?" , session["user_id"])

        # if the user tries to sell more shares than they have
        if int(shares) > int(table[0]["shares"]):
            return apology("You do not have enough Shares", 400)

        # make a variable for name and symbol
        name=quote["name"]
        symbol=quote["symbol"]

        # save the latest price of the share
        price=int(quote["price"])

        # find out the total "price" for selling that amount of shares
        total_price = shares * price * -1

        # select the user's cash
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

        # find the user's new balance
        newbalance = int(cash[0]["cash"]) - total_price

        # insert this transaction in the historic
        db.execute("INSERT INTO historic (client_id, type, symbol, Price, shares, total) VALUES (?, ?, ?, ?, ?, ?)", session["user_id"],"sell", symbol, price, - shares, total_price)

        # update the user's cash
        db.execute("UPDATE users Set cash = ? WHERE  id = ?", newbalance, session["user_id"])

        # turn the total price as positive to make it easier to visualize
        total_price = total_price * -1

        # return the page with the needed info
        return render_template("sold.html", name=name, price=price, symbol=symbol, cash=cash[0]["cash"], total_price=total_price,newbalance=newbalance)

    # if they arrived here throught get
    if request.method == "GET":

        # Select all distincts symbols from the user's historic
        table = db.execute("SELECT DISTINCT symbol FROM historic WHERE client_id = ?" , session["user_id"])

        # render the page
        return render_template("sell.html", table=table)
    return apology("TODO")

