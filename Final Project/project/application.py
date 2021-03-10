import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, usd

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
db = SQL("sqlite:///shopping.db")

@app.route('/')
@login_required
def index():
    return apology('todo')

@app.route('/login')
def login():
    '''shows two buttons'''
    return render_template('login.html')

@app.route('/buy', methods = ['GET', 'POST'])
@login_required
def buy():
    '''Buy something from list'''

    if request.method == 'GET':
        return render_template('buy.html')

    else:
        # ensure that item name is given
        if not request.form.get('item'):
            return apology('provide an item name', 403)

        elif not request.form.get('quantity'):
            return apology('provide the quantity', 403)

        # adding data into database
        item = request.form.get('item')
        quantity = request.form.get('quantity')
        Customer_ID = session['user_id']

        db.execute('INSERT INTO orders (Customer_ID, item, quantity) VALUES (:Customer_ID, :item, :quantity)', Customer_ID = Customer_ID, item = item, quantity = quantity)

        # redirect to my orders
        return redirect('/my_orders')

@app.route("/login_c", methods=["GET", "POST"])
def login_c():
    """Log user in (customer)"""

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
        rows = db.execute("SELECT * FROM users_c WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["password"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["Customer_ID"]

        # Redirect user to home page
        return redirect("/my_orders")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login_c.html")

@app.route("/login_s", methods=["GET", "POST"])
def login_s():
    """Log user in (shop)"""

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
        rows = db.execute("SELECT * FROM users_s WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["password"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["Shop_ID"]

        # Redirect user to home page
        return redirect("/orders")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login_s.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")

@app.route('/quote')
@login_required
def quote():
    ''' Get the list of products '''

    items = db.execute('SELECT * FROM items ORDER BY item ASC')
    return render_template('quote.html', items = items)

@app.route('/add', methods = ['GET', 'POST'])
@login_required
def add():
    """add new items to the list"""
    if request.method == 'GET':
        return render_template('add.html')

    else:
        # ensure item name is submitted
        if not request.form.get('item'):
            return apology('must provide item name')

        # ensure price is submitted
        if not request.form.get('price'):
            return apology('must provide a price')

        # ensure category
        if not request.form.get('category'):
            return apology('must provide a category')

        # adding data to database
        item = request.form.get('item')
        category = request.form.get('category')
        price = request.form.get('price')

        db.execute('INSERT INTO items (item, category, price) VALUES (:item, :category, :price)', item = item, category = category, price = price)

        # redirect to homepage
        return redirect('/orders')

@app.route('/register_c', methods = ['GET', 'POST'])
def register_c():
    if request.method == 'GET':
        return render_template('register_c.html')

    else:
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

        db.execute('INSERT INTO users_c (username, password) VALUES (:username, :password)', username = username, password = password)

        # redirect
        return redirect('/')

@app.route('/register_s', methods = ['GET', 'POST'])
def register_s():
    if request.method == 'GET':
        return render_template('register_s.html')

    else:
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

        db.execute('INSERT INTO users_s (username, password) VALUES (:username, :password)', username = username, password = password)

        # redirect
        return redirect('/')

@app.route('/orders')
@login_required
def orders():
    ''' for shops '''
    orders = db.execute("SELECT * FROM orders")
    return render_template('orders.html', orders = orders)

@app.route('/my_orders')
@login_required
def my_orders():
    ''' for customers '''
    my_orders = db.execute('SELECT * FROM orders WHERE Customer_ID = :user_id ORDER BY Order_ID ASC', user_id = session['user_id'])
    return render_template('my_orders.html', my_orders = my_orders)

@app.route('/customers')
@login_required
def customers():
    ''' shows link between id and names'''
    customers = db.execute('SELECT * FROM users_c')
    return render_template('customers.html', customers = customers)

@app.route('/deliver', methods = ['GET', 'POST'])
@login_required
def deliver():
    ''' remove the delivered items from database'''
    if request.method == 'GET':
        return render_template('deliver.html')

    else:
        deliver_ID = request.form.get('deliver')

        db.execute('DELETE FROM orders WHERE Order_ID = :Order_ID', Order_ID = deliver_ID)
        return redirect('/orders')

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)