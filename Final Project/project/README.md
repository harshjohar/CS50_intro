# Final Project - CS50
## $hop HERE

The project is a web based application. It can be used by the shopkeepers and the customers to sell and buy items respectively.
I learned to do all the stuff from this course only, I have my 100% effort on this application.
***

#### Languages used:
* Python
* CSS
* HTML
* Flask
* Javascript
* Bootstrap
* sqlite3

---

### How the website works?
The idea is simple. The user can register either as shopkeeper or customer.
During registration you need to enter these fields:

** Username **
** Password ** : it is checked to match, and is hashed after checks are done

_ Customer _ registeration registers the user as a customer, The available facilities in the app are to list all the available items, order those from the shopkeeper and have a lokk at user's own orders.

For _ shopkeepers _ , there are even more features available. They can add items, have a look at all the orders, complete an order using deliver option and have a look at all the customers' name.

#### Routing
Each route checks if the user is authenticated i.e. username and password is correct. Moreover a customer have no access to a shopkeeper's dashboard and vice versa.

#### Sessions
The webpage uses sessions to confirm that user is registered. Once the user logins, his credentials are checked.
Once everything passes a session is created (serialized and deserialized) and stored in the cookies. The server attaches user to subsequent requests, so the back-end can easily access the details, like roles: customer, shopkeeper.

#### Database
Database is used as a back-end in this application. They are bridged with html via flask and python.
The database stores all the information regarding the users(both customer and shopkeeper), the list of all items, the orders placed and many more details.

### Features
#### For Shopkeeper
* Add new items to sale list
* Deliver the placed orders by customers
* Look up the list of all customers along with their Customer_ID
* Look up all the orders placed by all the customers

#### For customers
* Look up at the list of all the items added by shopkeepers
* Place an order
* Look up at the list of user's orders


#### Areas of improvement
* A payment gateway may be added
* Buy option can be made more interactive
* Interface can be made more user-friendly