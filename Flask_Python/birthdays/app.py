import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])w
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database

        # adding entry
        Name = request.form.get("name")
        try:
            Month = int(request.form.get("month"))
        except:
            return redirect("/")
        try:
            Day = int(request.form.get("day"))
        except:
            return redirect("/")

        if Name and 1<=Month<=12 and 1<=Day<=31:
            db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", Name, Month, Day)

        #comfirm adition
        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html

        # Displaying the entries
        table = db.execute("SELECT * FROM birthdays")
        return render_template("index.html", table=table)

@app.route("/delete", methods=["POST"])
def delete():
        Name = request.form.get("name")
        try:
            Month = int(request.form.get("month"))
        except:
            return redirect("/")
        try:
            Day = int(request.form.get("day"))
        except:
            return redirect("/")

        if Name and 1<=Month<=12 and 1<=Day<=31:
            db.execute("DELETE FROM birthdays WHERE name = ? and month = ? and day = ?", Name, Month, Day)

        return redirect("/")

@app.route("/update", methods=["POST"])
def update():
        Name = request.form.get("name")
        try:
            Month = int(request.form.get("month"))
        except:
            return redirect("/")
        try:
            Day = int(request.form.get("day"))
        except:
            return redirect("/")

        Name2 = request.form.get("name2")
        try:
            Month2 = int(request.form.get("month2"))
        except:
            return redirect("/")
        try:
            Day2 = int(request.form.get("day2"))
        except:
            return redirect("/")
        if Name and 1<=Month<=12 and 1<=Day<=31 and Name2 and 1<=Month2<=12 and 1<=Day2<=31:
            db.execute("UPDATE birthdays SET name = ? WHERE name = ? and month = ? and day = ?", Name2, Name, Month, Day);

            db.execute("UPDATE birthdays SET month = ? WHERE name = ? and month = ? and day = ?", Month2, Name2, Month, Day);

            db.execute("UPDATE birthdays SET day = ? WHERE name = ? and month = ? and day = ?", Day2, Name2, Month2, Day);
        return redirect("/")
