#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    const double dollar_rate = 165.0;
    const double euro_rate = 193.0;
    const double sales_tax_rate_2 = 0.02; //2% TAX
    const double sales_tax_rate_5 = 0.05; //5% TAX

    const double chicken_karahi = 1800;
    const double chicken_tikka = 2000;
    const double chicken_haleem = 2200;
    const double creamy_chicken = 2500;
    const double chicken_handi = 800;

    int quantity, choice_dish, choice_curr;
    double dish_price, total_price, sales_tax, currency_rate, total_bill = 0,final_bill;

    do {
       cout<<"|------------------------------------------------|"<<endl;
       cout<<"|         WELCOME TO RAMEEN'S FOOD POINT         |"<<endl;
       cout<<"|------------------------------------------------|"<<endl;
       cout<<"|------------------------------------------------|"<<endl;
       cout<<"|                      MENU                      |"<<endl;
       cout<<"|------------------------------------------------|"<<endl;
       cout<<"|************************************************|"<<endl;
       cout<<"|     Enter 101... to order Chicken Karahi       |"<<endl;
       cout<<"|     Enter 102... to order Chicken Tikka        |"<<endl;
       cout<<"|     Enter 103... to order Chicken Haleem       |"<<endl;
       cout<<"|     Enter 104... to order Creamy Chicken       |"<<endl;
       cout<<"|     Enter 105... to order Chicken Handi        |"<<endl;
       cout<<"|     Enter 0... to exit MENU                    |"<<endl;

       
        cout << "Enter item code to buy..." << endl;
        cin >> choice_dish;
        
        if (choice_dish==0) {
            break;
        }
        
        if (choice_dish < 101 || choice_dish > 105) {
            cout << "Invalid choice. Please try again." << endl;
            continue;
        }

        cout << "Enter quantity of selected item in kg..." << endl;
        cin >> quantity;

        while (quantity<= 0) {
            cout << "Invalid quantity. Please enter a positive value." << endl;
            cin>>quantity;
        }
        switch (choice_dish) {
            case 101:
                dish_price=chicken_karahi * quantity;
                break;
            case 102:
                dish_price=chicken_tikka * quantity;
                break;
            case 103:
                dish_price=chicken_haleem * quantity;
                break;
            case 104:
                dish_price=creamy_chicken * quantity;
                break;
            case 105:
                dish_price=chicken_handi * quantity;
                break;
            default:
                cout<< "Invalid choice. Please try again"<< endl;
                continue;
        }
        if (dish_price > 1000 && dish_price <= 3000) {
            sales_tax = dish_price * sales_tax_rate_2;
        } else if (dish_price > 3000) {
            sales_tax = dish_price * sales_tax_rate_5;
        }else{
        	sales_tax = 0;
		}

        total_price = dish_price + sales_tax;
        total_bill+= total_price;
        cout << "Item: " <<choice_dish<< ", Quantity: " <<quantity<< ", Price: " <<dish_price<< endl;
        cout << "Sales Tax: " <<fixed<< setprecision(2) <<sales_tax<< endl;
        cout << "Total Price: " <<fixed<< setprecision(2) <<total_price<< endl;
    }while(true);
    cout << "Your Total Bill in PKR is: "<< fixed << setprecision(2) << total_bill << endl;
     do {
        cout << "Choose your currency for payment." << endl;
        cout << "Enter 1... to select Pakistani Rupee"<< endl;
        cout << "Enter 2... to select Euro"<< endl;
        cout << "Enter 3... to select Dollar"<< endl;
        cin >> choice_curr;

        if (choice_curr != 1 && choice_curr != 2 && choice_curr != 3) {
            cout << "Invalid currency choice. Please try again"<<endl;
        }
        }while(choice_curr!= 1 &&choice_curr != 2 && choice_curr != 3);
        currency_rate=1.0;
        switch (choice_curr) {
            case 2:
                currency_rate=euro_rate;
                break;
            case 3:
                currency_rate=dollar_rate;
                break;
    }
    if (choice_curr == 0) {
        cout << "Error: Invalid currency rate."<<endl;
        return 1; // exit with an error code
    }

        final_bill=total_bill/ currency_rate;
        if (choice_curr == 1) {
        cout <<"Your total bill in PKR is " << fixed << setprecision(2) << final_bill << endl;
    } else if (choice_curr == 2) {
        cout << "Your total bill in EUR is " << fixed << setprecision(2) << final_bill << endl;
    } else {
        cout << "Your total bill in USD is" << fixed << setprecision(2) << final_bill << endl;
    }
    cout<<"THANK YOU FOR ORDERING!";

    return 0;
}
