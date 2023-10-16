import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.after_request
def after_request(response):
  """Ensure responses are cached"""
  response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
  response.headers["Expires"] = 0
  response.headers["Pragma"] = "no-cache"
  return response

@app.route("/")
@login_required
def index():
  """Show portfolio of stocks"""
  # Get user's stocks and shares
  stocks = db.execute(
      "SELECT symbol, SUM(shares) AS total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING total_shares > 0",
      user_id=session["user_id"],
  )

  # Get user's cash balance
  cash = db.execute(
      "SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"]
  )[0]["cash"]

  # Initialize variables for total values
  total_value = cash
  grand_total = cash

  # Iterate over stocks and add price and total value
  for stock in stocks:
    quote = lookup(stock["symbol"])
    stock["name"] = quote["name"]
    stock["price"] = quote["price"]
    stock["value"] = stock["price"] * stock["total_shares"]
    total_value += stock["value"]
    grand_total += stock["value"]

  return render_template(
      "index.html",
      stocks=stocks,
      cash=cash,
      total_value=total_value,
      grand_total=grand_total,
  )

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
  """Buy shares of stock"""
  # User reached route via POST (as by submitting a form via POST)
  if request.method == "POST":
      symbol = request.form.get("symbol").upper()
      shares = request.form.get("shares")

      if not symbol:
        return apology("Must provide symbol")
      elif not shares or not shares.isdigit() or inst(shares) <= 0:
        return apology("Must provide a positive integer of shares")

      quote = lookup(symbol)
      if quote is None:
          return apology("Symbol not found")

      # vars used to calculate stock price vs user cash
      price = quote["price"]
      total_cost = int(shares) * price
      cash = db.execute(
          "SELECT cash FROM users WHERE id = :user_id", user_id = session["user_id"]
      )[0]["cash"]

@app.route("/history")
@login_required
def history():

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
    rows = db.execute(
        "SELECT * FROM users WHERE username = ?", request.form.get("username")
    )

    # Ensure username exists and password is correct
    if len(rows) != 1 or not check_password_hash(
        rows[0]["hash"], request.form.get("password")
    ):
        return apology("invalid username and/or password", 403)

    # Remember which user has logged in
    session["user_id"] = rows[0]["id"]

    # Redirect user to home page
    return redirect("/")

# User reached route via GET (as by clicking a link or via redirect)
else:
    return render_template("login.html")

@app.route("/logout")
def logout():
  """ Log user out"""
  # Forget any user_id
  session.clear()

  # Redirect user to login form
  return redirect("/")

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
  """Get stock quote."""
  # User reached route via GET (as by clicking a link or via redirect)
  if request.method == "GET":
    return render_template("quote.html")

  # via POST method
  else:
      symbol = request.form.get("symbol")

      # using var above, validate user's input
      if not symbol:
          return apology("Invalid Symbol")

      stock = lookup(symbol.upper())

      # If user leaves form blank
      if stock == None:
          return apology("Blank Symbol")

      return render_template(
          "quoted.html",
          name=stock["name"],
          price=stock["price"],
          symbol=stock["symbol"],
      )


@app.route("/register", methods=["GET", "POST"])
def register():
  """ Register user"""
  # User reached route via GET (as by clicking a link or via redirect)
  if request.method == "GET":
      return render_template("register.html")

  # submit user's input via POST
  else:
      username = request.form.get("username")
      password = request.form.get("password")
      confirmation = request.form.get("confirmation")

      # render apology if user's input is blank
      if not username:
          return apology("Invalid username")

      # render apology if either input for pw or conf is blank
      if not password:
          return apology("Invalid password")

      if not confirmation:
          return apology("Missing confirmation")

      # render apology if passwords don't match
      if password != confirmation:
          return apology("Passwords don't match")

      # abstract function into a var for easier use
      hash = generate_password_hash(confirmation)

      # INSERT the new user into users, hash the user's password with generate_password_hash
      try:
          new_user = db.execute(
              "INSERT INTO users (username, hash) VALUES (?, ?)", username, hash
          )

      # render apology if username already exists
      except:
          return apology("Username already exists")

      # Use session to remember new user
      session["user_id"] = new_user

      # Redirect to main route
      return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
  """ Sell shares of stock"""
  # Get user's 
