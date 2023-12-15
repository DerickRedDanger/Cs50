-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Checking on the crime report for the Theft of the duck.
Select *
from crime_scene_reports
where year = 2021
and month = 7
and day = 28
and street = "Humphrey Street";
-- it happened at 10:15 am, 3 witnesses, all mentioned the bakery
-- Checking interviews the interviews of the witness for crimes at that day.
Select *
from interviews
where year = 2021
and month = 7
and day = 28;
-- considering what is said there, the 3 witness are Ruth, Eugene and Raymond.
-- Ruth : the thief got in a car in the bakry parking lot +-10 mins after the theft. look for car that left the parking in that time.
-- Eugene : the thief is someone he know, but not by name. before he arrived at the bakery, when he was walking by the ATM on Leggett Street, he saw the thief there withdrawing money.
-- Raymond : as the thief left the bakery, they called someone and talked for less than a min. they plan to take the earliest flight from fiftyville tomorrow (29/7/2021), and asked helper to purchace the ticket.
-- considering the leads and options, the call seemed to be the one easiest to narrow down the suspect and accomplice, so i started there.
SELECT *
FROM phone_calls
JOIN people
ON phone_calls.caller = people.phone_number
WHERE phone_calls.year = 2021
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration < 60;

SELECT *
FROM phone_calls
JOIN people
ON phone_calls.receiver = people.phone_number
WHERE phone_calls.year = 2021
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration < 60;
-- That returned me 8 suspects for thief and 9 for accomplince. since i got a few names, i tried to use them and the flight to narrow down who is who
SELECT *
FROM flights
WHERE flights.year = 2021
AND flights.month = 7
AND flights.day = 29
ORDER BY hour;
-- that returned me 5 flights, all from the same origin airport, the earliest being one at 8 hours and 20 minutes, it's id is 36.
-- as a safety check, i checked what's the name of the airport from where all thses flights came from and to where it wemt
SELECT *
FROM airports
WHERE id = 8;
SELECT *
FROM airports
WHERE id = 4;
-- it returned Fiftyville Regional Airport, since the theft happened in Fiftyville, it's safe to say the one at 8:20 is the one we are looking for.
-- and it headed to LaGuardia Airport, New York City
-- now it's time to check everyone that was in that flight and compare to the phone calls to narrow down the suspect.
SELECT people.name
from people
join passengers
join flights
on flights.id = passengers.flight_id
and passengers.passport_number = people.passport_number
WHERE flights.id = 36;
-- that returned 8 suspects. comparing to our original list of suspects for thief and accomplice.
SELECT people.name AS Caller,phone_calls.caller AS Phone
FROM phone_calls
JOIN people
ON phone_calls.caller = people.phone_number
WHERE phone_calls.year = 2021
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration < 60;

SELECT people.name AS Receiver
FROM phone_calls
JOIN people
ON phone_calls.receiver = people.phone_number
WHERE phone_calls.year = 2021
AND phone_calls.month = 7
AND phone_calls.day = 28
AND phone_calls.duration < 60;
-- returned 5 suspects. Sofia, Bruce, Kelsey, Taylor and Kenny. which in turn reduced our list of suspects for accomplice to 6 people. Jack, Robin, Larry/Melissa, James, Doris
-- Considering there was nothing else to be gained from this lead, I switched my focus to the Ruth's lead since it seemed the more precise one.
SELECT *
FROM bakery_security_logs
WHERE year = 2021
and month = 7
and day = 28
and hour = 10
and minute BETWEEN 15 AND 26;
-- that narrows down to 8 cars. checking their owners.
SELECT people.name
FROM bakery_security_logs
join people
on bakery_security_logs.license_plate = people.license_plate
WHERE year = 2021
and month = 7
and day = 28
and hour = 10
and minute BETWEEN 15 AND 25;
-- that led us to 8 people. comparing to our original list of suspects, we can narrow it down to 3 people; Bruce, Sofia and Kelsey.
SELECT people.name
from atm_transactions
join bank_accounts
Join people
on atm_transactions.account_number = bank_accounts.account_number
and bank_accounts.person_id = people.id
WHERE year = 2021
and month = 7
and day = 28
and atm_location = "Leggett Street"
and transaction_type = "withdraw";
-- comparing to suspect list, only Bruce is here. looking back at line 81, we can see that Bruce called Robin, so he is the accomplice.
-- Thus Bruce is the Thief, Robin is the accomplice and the city he escaped to is LaGuardia.

