import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    stocks = db.execute('SELECT * FROM stocks WHERE user_id = :user_id ORDER BY symbol ASC', user_id = session['user_id'])
    user = db.execute('SELECT * FROM users WHERE id = :id', id = session['user_id'])
    grand_total = 0.0

    for i in range(len(stocks)):
        stock = lookup(stocks[i]['symbol'])
        stocks[i]['company'] = stock['name']
        stocks[i]['cur_price'] = "%.2f"%(stock['price'])
        stocks[i]['cur_total'] = '%.2f'%(float(stock['price']) * float(stocks[i]['shares']))
        stocks[i]['profit'] = '%.2f'%(float(stocks[i]['cur_total']) - float(stocks[i]['total']))
        grand_total += stocks[i]['total']
        stocks[i]['total'] = '%.2f'%(stocks[i]['total'])

    grand_total += float(user[0]['cash'])

    return render_template('index.html', stocks = stocks, cash = usd(user[0]['cash']), grand_total = usd(grand_total))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == 'GET':
        return render_template("buy.html")

    else:
        # no symbol matches
        if not request.form.get("symbol") or not request.form.get("shares") or int(request.form.get("shares")) < 1:
            return render_template("buy.html")

        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")
        user_id = session["user_id"]

        # lookup the stock
        stock = lookup(symbol)

        # ensure symbol exists
        if not stock:
            return apology("symbol not found")

        # calculate total price
        total_price = float(stock["price"]) * float(shares)

        user = db.execute("SELECT * FROM users WHERE id = :id", id = user_id)
        funds = float(user[0]["cash"])

        # check the budget of user
        if funds < total_price:
            return apology("not enough funds")

        funds_left = funds - total_price

        # check if the symbol is already owned
        stock_db = db.execute("SELECT * FROM stocks WHERE user_id = :user_id AND symbol = :symbol",
                                user_id = user_id, symbol = symbol)

        #update the new price if already owned
        if len(stock_db) == 1:
            new_shares = int(stock_db[0]["shares"]) + int(shares)
            new_total = float(stock_db[0]["total"]) + total_price
            new_pps = "%.2f"%(new_total / float(new_shares))
            # pps = price per share

            db.execute("UPDATE stocks SET shares = :shares, total = :total, pps = :pps WHERE user_id = :user_id AND symbol = :symbol",
                        shares = new_shares, total = new_total, pps = new_pps, user_id = user_id, symbol = symbol)

         # if not already owned
         # create a new entry in database
        else:
             db.execute('INSERT INTO stocks (user_id, symbol, shares, total, pps) VALUES (:user_id, :symbol, :shares, :total, :pps)',
                        user_id = user_id, symbol = symbol, shares = shares, total = total_price, pps = stock['price'])

        # modify the available funds
        db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash = funds_left, id = user_id)

        #add to history
        db.execute('INSERT INTO history (user_id, action, symbol, shares, pps) VALUES (:user_id, :action, :symbol, :shares, :pps)',
                    user_id = user_id, action = 1, symbol = symbol,  shares = shares, pps = stock['price'])

        # return to home page
        return redirect('/')
@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # retrieve history from db
    stocks = db.execute('SELECT * FROM history WHERE user_id = :user_id ORDER BY date DESC', user_id = session['user_id'])

    # calculate the total price of transaction
    for i in range(len(stocks)):
        stocks[i]['total'] = '%.2f'%(float(stocks[i]['shares']) * float(stocks[i]['pps']))

    #render the table
    return render_template('history.html', stocks = stocks)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
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
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # find the required stock
    if request.method == "POST":
        quote = lookup(request.form.get("symbol"))

        # if the symbol is invalid
        if quote == None:
            return apology("inavalid symbol", 400)

        # prints the line
        return render_template("quoted.html", quote = quote)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Ensure if both the passwords match
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("both passwords must match", 403)

        # adding data into database
        username = request.form.get("username")
        password = generate_password_hash(request.form.get("password"))

        db.execute('INSERT INTO users (username, hash) VALUES (:username, :hash)', username = username, hash = password)

        # Redirect user to home page
        return redirect('/')

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    stocks = db.execute('SELECT * FROM stocks WHERE user_id = :user_id', user_id = session['user_id'])

    if request.method == 'GET':
        return render_template('sell.html', stocks = stocks)

    else:
        # ensure quantity was mentioned
        if not request.form.get('shares') or int(request.form.get('shares')) < 1:
            return render_template('sell.html', stocks = stocks)

        symbol = request.form.get('symbol').upper()
        shares = request.form.get('shares')
        user_id = session['user_id']

        # retrieve the stock from db
        stock_db = db.execute('SELECT * FROM stocks WHERE user_id = :user_id AND symbol = :symbol', user_id = user_id, symbol = symbol)

        if stock_db:
            stock_db = stock_db[0]

        else:
            return render_template('sell.html', stoocks = stocks)

        # retrieve the user data from db
        user = db.execute('SELECT * FROM users WHERE id = :id', id = user_id)

        #ensure the quantity is available
        if int(shares) > stock_db['shares']:
            return apology('not enough shares')

        # lookup for stock
        stock = lookup(symbol)

        # calculate total price
        total_price = float(stock['price']) * float(shares)

        # modify the nubmer of shares owned
        if int(shares) == stock_db['shares']:
            db.execute('DELETE FROM stocks WHERE user_id = :user_id AND symbol = :symbol', user_id = user_id, symbol = symbol)

        else:
            new_shares = int(stock_db['shares']) - int(shares)
            new_total = float(new_shares) * float(stock_db['pps'])
            db.execute('UPDATE stocks SET shares = :shares, total = :total WHERE user_id = :user_id AND symbol = :symbol', shares = new_shares, total = new_total, user_id = user_id, symbol = symbol)

        # modify available funds
        funds_available = float(user[0]['cash']) + total_price
        db.execute('UPDATE users SET cash = :cash WHERE id = :id', cash = funds_available, id = user_id)

        # commit to history
        db.execute('INSERT INTO history(user_id, action, symbol, shares, pps) VALUES (:user_id, :action, :symbol, :shares, :pps)',user_id = user_id, action = 0, symbol = symbol, shares = shares, pps = stock['price'])

        #success
        return redirect('/')

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)