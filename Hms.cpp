#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include <iomanip>
#include <sstream>


using namespace  std;


class Booking
{

private:
    string Name;
    int RoomNumber;
    int Days;
    int PricePerNight;


public:    
    string GetName()
    {
        return Name;
        
    }


    int GetRoomNumber()
    {

        return RoomNumber;

    }   
    
    int GetDays()
    {
        return Days;
    }

    int GetPrices()
    {
        return PricePerNight;
    }

    float GetTotalCost()
    {
        return Days * PricePerNight;
    }


void SetBookingData(string name, int room, int days, int price)
{
    Name = name;
    RoomNumber = room;
    Days = days;
    PricePerNight = price;
}


public:

    void AddBooking()
    {

        cout << "Enter the client name please: \n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, Name);

        cout << "Enter the room number please: \n";
        cin >> RoomNumber;


        cout << "Enter the numbers of reservation days: \n";
        cin >> Days;


        cout << "Enter the price per night: \n";
        cin >> PricePerNight;

    }




    void DisplayBookingCost()
    {
        float totalcost = Days * PricePerNight;
        cout << "Total cost = " << totalcost << endl;
    }



    void DisplayBookingInfo()
    {

        cout << "-----------------------------" << endl;
        cout << "Booking Details" << endl;
        cout << "-----------------------------" << endl;
        cout << left << setw(20) << "Customer Name:" << Name << endl;
        cout << "Room Number: " << RoomNumber << endl;
        cout << "Days: " << Days << endl;
        cout << "Price per Night: " << PricePerNight << endl;
        cout << "\n----------------------------------\n";
        DisplayBookingCost();
        cout << "-----------------------------" << endl;

    }



};


void LoadFromFile(vector<Booking>& vBookings)
{
    fstream MyFile("Booking.txt",ios::in);

    if(MyFile.is_open())
    {

        string line;
    
        while (getline(MyFile,line))
        {
            if (line.empty())
            continue;
            string name;
            Booking b;
            int room, days, price;
            stringstream ss(line);

            getline(ss, name, ',');

            ss >> room;
            ss.ignore();

            ss >> days;
            ss.ignore();

            ss >> price;
            
            
            b.SetBookingData(name, room, days, price);
            vBookings.push_back(b);           
        }
    
        MyFile.close();
    }
    else
    {
    
        cout << "Error: Could not open file!\n";

    }

}


void UpdateBook(vector<Booking>& vBookings)
{

    string nameToUpdate;
     cout << "\n✏️ Update Booking\n";
    cout << "Enter the customer name to update: ";


    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, nameToUpdate);


    bool found = false;

    for(Booking& b: vBookings)
    {

        if(b.GetName() == nameToUpdate)
        {


        cout << "\n✅ Booking found. Current details:\n";
        b.DisplayBookingInfo();

        cout << "\nEnter new details below:\n";

        int newRoom, newDays, newPrice;


        cout << "Enter new room number: ";
        cin >> newRoom;

        cout << "Enter new number of days: ";
        cin >> newDays;

        cout << "Enter new price per night: ";
        cin >> newPrice;


        b.SetBookingData(nameToUpdate, newRoom, newDays, newPrice);

        SaveAllBookingToFile(vBookings);


        cout << "\n🟢 Booking updated successfully!\n";
        found = true;
        break;
    }

    }
    if(!found)
    {
        cout << "\n❌ No booking found for this name!\n";

    }

}


void SaveToFile(Booking& b)
{

    fstream MyFile("Booking.txt", ios:: out | ios::app);

    if(MyFile.is_open())
    {

        MyFile << b.GetName() << ","
               << b.GetRoomNumber() << ","
               << b.GetDays() << "," 
               << b.GetPrices() 
               << endl;       
        
        MyFile.close();

    }
      else
    {
        cout << "Error: Could not open file!\n";
    }


}


void SaveAllBookingToFile(vector<Booking>& vBooking)
{

    fstream MyFile("Booking.txt", ios::out | ios::trunc);
   if(MyFile.is_open())
    {

        for(Booking& b: vBooking)
        {

        MyFile << b.GetName() << ","
               << b.GetRoomNumber() << ","
               << b.GetDays() << "," 
               << b.GetPrices() 
               << endl;       
        }

        MyFile.close();

    }
      else
    {
        cout << "Error: Could not open file!\n";
    }

}


void SearchByName(vector <Booking>& vBookings)
{

    cout << "\n🔍 Search Booking By Name\n";
    cout << "Enter the customer name to search: ";

    cin.ignore(numeric_limits<streamsize>::max(),'\n');


    string nameToSearch;
    getline(cin, nameToSearch);


    bool found = false;


    for(Booking& b: vBookings)
    {
        if(b.GetName() == nameToSearch)
        {

            cout << "\n✅ Booking found!\n";
            b.DisplayBookingInfo();

            found = true;
            break;

        }

    }

     if(!found)
    {
        cout << "\n❌ No booking found for this name!\n";

    }

}



void MainMenu()
{

    vector <Booking> vBookings;
    LoadFromFile(vBookings);

    int choice = 0;
    while (choice != 6)
    {


       cout << "\n\033[36m====== Hotel Booking System ======\033[0m\n";

        cout << "1. Add New Booking" << endl;
        cout << "----------------------------------\n";
        cout << "2. View All Bookings" << endl;
        cout << "----------------------------------\n";
        cout << "3. Search Booking" << endl;
        cout << "----------------------------------\n";
        cout << "4. Cancel Booking" << endl;
        cout << "----------------------------------\n";
        cout << "5. Update Booking" << endl;
        cout << "----------------------------------\n";
        cout << "6. Exit" << endl;



   
        cout << "Enter your choice please: " << endl;
  
        cin >> choice;

     
     
        string nameToSearch;
        string nameToDelete;

        switch (choice)
        {

        case 1:
        {
            Booking newbooking;

            cout << "\n🟢 Add New Booking\n";
            newbooking.AddBooking();
            vBookings.push_back(newbooking);

            SaveToFile(newbooking);




            cout << "\n🟢 Add New Booking\n";
            newbooking.DisplayBookingInfo();
            

            break;
        }
        case 2:
        {
           
            cout << "\n\033[36m===========================================\033[0m\n";
            cout << "         🏨 Hotel Booking System Menu\n";
            cout << "\033[36m===========================================\033[0m\n";


            if(vBookings.empty())
            {
                cout << "\033[31m❌ No bookings found!\033[0m\n";
            }

            else
            {
                int counter = 1;

                for(Booking& booking : vBookings)
                {   
                    cout << "#" << counter << " | Name: " << booking.GetName() << endl;
                    cout << "   | Room: " << booking.GetRoomNumber() << endl;
                    cout << "   | Days: " << booking.GetDays() << endl;
                    cout << "   | Price/Night: " << booking.GetPrices() << endl;
                    cout << "   | Total: " << booking.GetTotalCost() << endl;
                    cout << "-------------------------------------------\n";
                    counter++;

                }
                    cout << "✅ Total Bookings: " << vBookings.size() << endl;
                    cout << "===========================================\n";

            }

            break;
        }


        case 3:
        {
            SearchByName(vBookings);
            break;
        }



        case 4:
         {
            bool found = false;

            cout << "\n🗑️ Cancel Booking\n";

            cout << "Enter the client name to delete: " << endl;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, nameToDelete);


            for(auto it = vBookings.begin(); it !=  vBookings.end(); ++it)
            {
                if(it->GetName() == nameToDelete)
                {
                    cout << "\033[32m✅ Booking successfully deleted!\033[0m\n";
                    vBookings.erase(it);
                    SaveAllBookingToFile(vBookings);
                    cout << "\n----------------------------------\n";
                    found = true;
                    break;
                }
                
            }

            if(!found)
            {
                
                cout << "\033[31m❌ No booking found for this name!\033[0m\n";
            }

            cout << "\n\033[33mUpdated Booking List:\033[0m\n";

            cout << "===========================\n";


            if(vBookings.empty())
            {
                cout << "No bookings remaining.\n";
            }


            else
            {

                int counter = 1;

                for(Booking& booking : vBookings)
                {   
                    cout << "#" << counter << " | Name: " << booking.GetName() << endl;
                    cout << "   | Room: " << booking.GetRoomNumber() << endl;
                    cout << "   | Days: " << booking.GetDays() << endl;
                    cout << "   | Price/Night: " << booking.GetPrices() << endl;
                    cout << "   | Total: " << booking.GetTotalCost() << endl;
                    cout << "-------------------------------------------\n";
                    counter++;
                }
                cout << "✅ Total Bookings: " << vBookings.size() << endl;
                cout << "===========================================\n";
            }
            break;
        }

        case 5:
        {

            UpdateBook(vBookings);
            break;

        }

        case 6:
        {

            cout << "\n\033[36m===========================================\033[0m\n";
            cout << "     👋 Thank you for using our system!\n";
            cout << "          Have a nice day! 🌟\n";
            cout << "\033[36m===========================================\033[0m\n";
            break;
        }
            default:
            cout << "\n❗ Invalid choice. Please try again.\n";
            break;
        }


        }
    }
    





int main()
{
    MainMenu();    

    return 0;
}