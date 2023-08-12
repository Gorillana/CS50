import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use/access SQLite database
db = SQL("sqlite:///birthdays.db")

@app.after_request
def after_request(response):
    """ Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        # Access bday form data
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        # Use db execute to use SQL queries to add info to db
        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)

        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        # Use db exec to use SQL to access all of the data from birthdays
        birthdays = db.execute("SELECT * FROM birthdays")

        # Render bdays page
        # first birthdays is a new var calling to the established var birthdays from above
        return render_template("index.html", birthdays=birthdays)
