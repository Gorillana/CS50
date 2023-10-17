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

      # Compare current user cash to cost of stocks
      if cash < total_cost:
          return apology("Insufficient funds")

      # Update users table
      db.execute(
          "UPDATE users SET cash = cash - :total_cost WHERE id = :user_id",
          total_cost=total_cost,
          user_id=session["user_id"],
      )

      # Add the purchase to the history table
      db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price, type) VALUES (:user_id, :symbol, :shares, :price, :type)",
            user_id=session["user_id"],
            symbol=symbol,
            shares=shares,
            price=price,
            type="Buy",
        )

      flash(f"Bought {shares} shares of {symbol} for {usd(total_cost)}!")
      return redirect("/")

  else:
      return render_template("buy.html")

@app.route("/history")
@login_required
def history():
  """Show history of transactions"""
  # Query database for user's transactions, ordered by most recent first
  transactions = db.execute(
      "SELECT * FROM transactions WHERE user_id = :user_id ORDER BY timestamp DESC",
      user_id=session["user_id"],
      )

  # Render history page with transactions
  return render_template("history.html", transactions=transactions)

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
  # Get user's stocks
  stocks = db.execute(
      "SELECT symbol, SUM(shares) AS total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING total_shares > 0",
      user_id=session["user_id"],
      )

  # If the user submits the form
  if request.method == "POST":
      #create vars for if statements
      symbol = request.form.get("symbol").upper()
      shares = request.form.get("shares")
      if not symbol:
          return apology("Must provide symbol", 400)
      elif not shares or not shares.isdigit() or int(shares) <= 0:
          return apology("Must provide a positive number of shares", 400)
      else:
          shares = int(shares)

      # cycle through the stocks user has purchased
      for stock in stocks:
          if stock["symbol"] == symbol:
              if stock["total_shares"] < shares:
                  return apology("Not enough shares", 400)
              else:
                  # Get quote
                  quote = lookup(symbol)
                  if quote is None:
                      return apology("Symbol not found", 400)
                  price = quote["price"]
                  total_sale = shares * price

                  # Update users table
                  db.execute(
                      "UPDATE users SET cash = cash + :total_sale WHERE id = :user_id",
                      total_sale=total_sale,
                      user_id=session["user_id"],
                      )

                  # Add the sale to the history table
                  db.execute(
                      "INSERT INTO transactions (user_id, symbol, shares, price, type) VALUES (:user_id, :symbol, :shares, :price, :type)",
                      user_id=session["user_id"],
                      symbol=symbol,
                      shares=(-1) * shares,
                      price=price,
                      type="Sell,
                      )

                  flash(f"Sold {shares} shares of {symbol} for {usd(total_sale)}!")
                  return redirect("/")

      return apology("Nonexistent symbol", 400)

   # If the user visits the page
   else:
      return render_template("sell.html", stocks=stocks)

# Personal touch, allow user to change password
@app.route("/password", methods=["GET", "POST"])
@login_required
def password():
    """ Allow user to change password"""

    # get current user
    user_id = session["user_id"]

    if request.method == "POST":
        # create variables for if statements
        current_pwd = request.form.get("current-password")
        confirmation = request.form.get("current-confirmation")
        new_pwd = request.form.get("new-password")
        new_conf = request.form.get("new-confirmation")

        search_id = db.execute("SELECT * FROM users WHERE id = ?", user_id)

        if not current_pwd:
            return apology("Missing password!", 400)
        if not confirmation:
            return apology("Provide confirmation!", 400)
        if current_pwd != confirmation:
            return apology("Password and confirmation don't match!", 400)
        if not new_pwd:
            return apology("missing new password!", 400)
        if new_pwd != new_conf:
            return apology("New password and new confirmation don't match!", 400)
        if not check_password_hash(
            search_id[0]["hash"], request.form.get("current-password")
        ):
            return apology("Invalid password.", 400)

        hash_pd = generate_password_hash(new_pwd, method="pbdkf2:sha256", salt_length=8)

        db.execute("UPDATE users SET hash = ? WHERE id = ?", hash_pd, user_id)

        return redirect("/")

    # User arrived via GET method
    else:
        return render_template("password.html")
  
