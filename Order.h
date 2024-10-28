#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Base class for all orders
class Order {

public:
    bool* executed;     // Was the order executed?
    string* type;       // order type
	
    Order(): executed(new bool(false)), type(new string("Generic Order")) {};
    Order(string t): executed(new bool(false)), type(new string(t)) {};

    ~Order() {
		delete executed;
		delete type;
	}

    Order(const Order& rhs) {
		executed = new bool(*rhs.executed);
		type = new string(*rhs.type);
	}

    Order& operator=(const Order& rhs) {
		if (this != &rhs) {
			executed = new bool(*rhs.executed);
			type = new string(*rhs.type);
		}
		return *this;
	}

    bool validate() {
		return true;
	};

    void execute() {
		if (validate()) {
			*executed = true;
			cout << *type << " order executed successfully.\n";
		} else {
			cout << "Order is invalid.\n";
		}
	};
	
	friend ostream& operator<<(ostream& out, const Order& order) {
		Order& cOrder = const_cast <Order&>(order);
		
		out << "Order: " << *cOrder.type;
		if (*cOrder.executed) {
			out << " (Executed)";
		}
		return out;
	}
};

// OrdersList class to manage a list of orders
class OrdersList {
	
	int* ordersCount = new int(0);
	public:
		Order* orders; // List of pointers to Order objects
		
		OrdersList() {
			orders = new Order[0];
		}; // Constructor for OrdersList

		// Copy constructor for OrdersList
		OrdersList(const OrdersList& rhs) {
			orders = new Order[*rhs.ordersCount];
			ordersCount = new int(*rhs.ordersCount);
			for (int i = 0; i < *ordersCount; i++) {
				orders[i] = Order(rhs.orders[i]); 
			}
		};

		// Assignment operator for OrdersList
		OrdersList& operator=(const OrdersList& rhs) {
			if (this != &rhs) {
				orders = new Order[*rhs.ordersCount];
				ordersCount = new int(*rhs.ordersCount);
				for (int i = 0; i < *ordersCount; i++) {
					orders[i] = Order(rhs.orders[i]); 
				}
			}
			return *this;
		};

		~OrdersList() {
			delete [] orders;
			delete ordersCount;
		};
		
		int getOrdersCount() {
			return *ordersCount;
		}

		void addOrder(Order order) {
			Order* temp = new Order[*ordersCount + 1];
			for (int i = 0; i < *ordersCount; i++) {
				temp[i] = orders[i];
			}
			temp[*ordersCount] = order;
			orders = temp;
			*ordersCount = *ordersCount + 1;
		};

		// Move an order from one position to another within the list
		void moveOrder(size_t fromIndex, size_t toIndex) {
			if (0 > fromIndex
				|| fromIndex >= *ordersCount
				|| 0 > toIndex
				|| toIndex >= *ordersCount) {
				cout << "Invalid indices for moving orders." << endl;
				return;
			}
			
			Order dummy;
			dummy = orders[fromIndex];
			orders[fromIndex] = orders[toIndex];
			orders[toIndex] = dummy;
		};

		// Remove an order from the list by index
		void removeOrder(size_t index) {
			if (0 > index
				|| index >= *ordersCount) {
				cout << "Invalid indices for moving orders." << endl;
				return;
			}
			
			Order* temp = new Order[*ordersCount - 1];
			int tIndex = 0;
			for (int i = 0; i < *ordersCount; i++) {
				if (i == index) { continue; }
				temp[tIndex] = orders[i];
				tIndex++;
			}
			orders = temp;
			*ordersCount = *ordersCount - 1;
		};

		// Execute all valid orders in the list
		void executeOrders() {
			for (int i = 0; i < *ordersCount; i++) {
				orders[i].execute();
			}
		};
		
		friend ostream& operator<<(ostream& out, const OrdersList& ordersList) {
			OrdersList& cOrdersList = const_cast <OrdersList&>(ordersList);
			
			out << "OrdersList:\n";
			for (int i = 0; i < cOrdersList.getOrdersCount(); i++) {
				out << cOrdersList.orders[i] << endl;
			}
			return out;
		}
};

#endif
