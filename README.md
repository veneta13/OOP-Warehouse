# OOP-Warehouse
### Task for the OOP course @ FMI.

Write a program implementing a warehouse information system.

The program stores and processes data - the warehouse stock, in **text format**.

#### Product information

The following information is stored for each product:

- _name/product description_ - character string of arbitrary length
- _expiration date_
- _date of entry_ into the warehouse
- _manufacturer's name_
- _available quantity_
- _location_ (incl. section, shelf, position on shelf)
- _comment_ (arbitrary text)


#### Supported operations


| Operation                  | Description                                                                                                                    |
|----------------------------|--------------------------------------------------------------------------------------------------------------------------------|
| Display                    | displays information about available products in the warehouse                                                                 |
| Add a product              | adds a new product to the warehouse in dialog mode and checks it for correctness (*)                                           |
| Take out a product         | takes out a product from the warehouse in dialog mode and checks it for correctness (**)                                       |
| Make an availability query | reports all stock changes in a time period entered by the user, including adding and taking out products                       |
| Clearance                  | performs a clearance for a given date (***)                                                                                    |
| Save                       | saves warehouse information in a file                                                                                          |
| Load                       | reads warehouse information from a file                                                                                        |
| Exit                       | exits the program                                                                                                              |


_(*) Adding a new product complies with the following rules:_
- if a new product has a **different expiration date** than an existing one of the **same name**, it should be placed on **different place**;
- if there is enough space, **same products** with the **same expiration date** to be placed in **adjacent locations** in the warehouse 
(i.e. on the same shelf, if possible, if not - on adjacent shelves in one section, if possible, or if not - in adjacent sections);
- when displaying the list of available products the **total amount** of the products of the same name should be displayed, regardless of their expiration date.


_(**) Removing a product complies with the following rules:_
- given name and quantity, removes the corresponding products from the warehouse and **displays information** about the product and where it was stored;
- if there is more than one batch, the one with the earliest expiration date is removed first, 
then in the displayed one information about the performed action is noted the **quantity and location of each of the batches** that were reduced;
- in the case of an attempt to **take out more than what is available** the user is informed about the **availability** of the product
and the expiration date of the lots and opportunity to decide whether or not to take out what's available.


_(***) Stock clearance complies with the following rules:_
- clears the warehouse of all goods that **have expired** or are **about to expire** for a given date;
- information about the cleared goods is saved in text file named **cleanup-YYYY-MM-DD.txt** where YYYY-MM-DD is the date for which the clearance is performed.
