#include "executor.hpp"

/// Default constructor
Executor::Executor() {
    warehouse = new Warehouse;
}


/// Copy constructor
/// \param other executor to copy
Executor::Executor(Executor const& other) {
    warehouse = new Warehouse(*other.warehouse);
}


/// Copy assignment operator
/// \param other executor to copy
/// \return the updated executor
Executor& Executor::operator=(Executor const& other) {
    if (this != &other) {
        delete warehouse;
        warehouse = new Warehouse(*other.warehouse);
    }
    return *this;
}


/// Destructor
Executor::~Executor() {
    delete warehouse;
    warehouse = nullptr;
}


/// User interface menu
/// \param out output stream to write the menu in
/// \param in input stream to read user input from
/// \return if the program should exit
bool Executor::enter(std::ostream& out, std::istream& in) {
    out << "Available commands:\n"
        << "[1] List all products currently in warehouse\n"
        << "[2] Add a product to the warehouse\n"
        << "[3] Take out a product from the warehouse\n"
        << "[4] Make a query for all stocked and taken out products\n"
        << "[5] Cleanup expired and expiring products\n"
        << "[6] Load warehouse from file\n"
        << "[7] Save warehouse in file\n"
        << "[ ] Exit\n"
        << "\nEnter command code:\n";
    int code;
    in >> code;

    switch(code) {
        case 1 :
            list(out);
            break;
        case 2 :
            addProduct(out, in);
            break;
        case 3 :
            takeOutProduct(out, in);
            break;
        case 4 :
            makeQuery(out, in);
            break;
        case 5 :
            cleanup(out, in);
            break;
        case 6 :
            load(out, in);
            break;
        case 7 :
            save(out, in);
            break;
        default :
            return false;
    }

    return true;
}


/// Today date setter
/// \param out output stream to write the prompt in
/// \param in input stream to read date from
void Executor::setToday(std::ostream &out, std::istream &in) {
    Date date;
    out << "Enter today's date:\n";
    readDate(date, out, in);
    warehouse->setToday(date);
}


/// List all items currently in the warehouse
/// \param out output stream to write items in
void Executor::list(std::ostream& out) {
    out << (*warehouse);
}


/// Create and add product in the warehouse
/// \param out output stream to write prompts in
/// \param in input stream to read user input from
void Executor::addProduct(std::ostream& out, std::istream& in) {
    Product product;
    std::string str;
    int num = -1;

    out << "Enter product name:\n";
    in.ignore();
    getline(in, str);
    product.setName(str.c_str());

    out << "Enter product manufacturer:\n";
    getline(in, str);
    product.setManufacturer(str.c_str());

    while (num == -1) {
        out << "Enter product quantity:\n";
        in >> num;
        if (num < 1) {
            out << "WARNING! Product quantity must be a positive number\n";
            num = -1;
        }
    }
    product.setQuantity(num);

    Date date;
    out << "Set expiration date:\n";
    readDate(date, out, in);
    product.setExpirationDate(date);

    date = Date();
    out << "Set stocked date:\n";
    readDate(date, out, in);
    product.setStockedDate(date);

    out << "Enter a comment:\n";
    in.ignore();
    getline(in, str);
    product.setComment(str.c_str());

    if (warehouse->restock(product)) {
        out << "Product successfully added!\n";
    }
    else {
        out << "Product was NOT added!\n";
    }
}


/// Take out product from the warehouse
/// \param out output stream to write prompts in
/// \param in input stream to read user input from
void Executor::takeOutProduct(std::ostream& out, std::istream& in) {
    std::string str;
    int quantity;

    out << "Enter the name of the product you want to take out:\n";
    in.ignore();
    getline(in, str);

    out << "Enter the quantity you want to take out:\n";
    in >> quantity;

    if (warehouse->takeOutProduct(out, in, str.c_str(), quantity)) {
        out << "Product successfully taken out!\n";
    }
    else {
        out << "Product was NOT taken out!\n";
    }
}


/// Make expired and stocked query
/// \param out output stream to write prompts in
/// \param in input stream to read user input from
void Executor::makeQuery(std::ostream& out, std::istream& in) {
    Date from, to;

    out << "Enter start date:\n";
    readDate(from, out, in);
    out << "Enter end date:\n";
    readDate(to, out, in);

    warehouse->makeQuery(out, from, to);
}


/// Cleanup expired and expiring products from warehouse and save information in file
/// \param out output stream to write prompts in
/// \param in input stream to read user input from
void Executor::cleanup(std::ostream& out, std::istream& in) {
    Date date;
    std::ofstream file;
    std::string str;

    out << "Enter cleanup date:\n";
    readDate(date,out, in);
     str = "cleanup-";
     str += std::to_string(date.year);
     str += "-";
     str += std::to_string(date.month);
     str += "-";
     str += std::to_string(date.day);
     str += ".txt";

    file.open(str.c_str());
    if (!file) {
        out << "File could NOT be opened to save cleanup information!\n";
        return;
    }

    warehouse->cleanup(file, date);
    out << "Cleanup successful!\n";

    file.close();
}


/// Load warehouse information from file
/// \param out output stream to write prompts in
/// \param in input stream to read user input from
void Executor::load(std::ostream& out, std::istream& in) {
    std::string str;
    std::ifstream file;
    out << "Enter name of the warehouse file:\n";
    in.ignore();
    std::getline(in, str);

    file.open(str.c_str());
    if (!file) {
        out << "File could NOT be opened!\n";
        return;
    }

    fileManager.readFile(file, *warehouse);
    out << "\nFile read successfully!\n";

    file.close();
}


/// Save warehouse information in file
/// \param out output stream to write prompts in
/// \param in input stream to read user input from
void Executor::save(std::ostream& out, std::istream& in) {
    std::string str;
    std::ofstream file;
    out << "Enter name of the warehouse file:\n";
    in.ignore();
    std::getline(in, str);

    file.open(str.c_str());
    if (!file.good()) {
        out << "File count NOT be opened!\n";
        return;
    }

    fileManager.writeFile(file, *warehouse);
    out << "\nWarehouse saved successfully!\n";

    file.close();
}


/// Update date via user input
/// \param date the date object to update
/// \param out output stream to write prompts in
/// \param in input stream to read user input from
void Executor::readDate(Date& date, std::ostream& out, std::istream& in) {
    while (!date.isValid()) {
        Date d;
        int num;
        out << "Enter day:\n";
        in >> num;
        d.day = num;

        out << "Enter month:\n";
        in >> num;
        d.month = num;

        out << "Enter year:\n";
        in >> num;
        d.year = num;

        date = d;
    }
}

