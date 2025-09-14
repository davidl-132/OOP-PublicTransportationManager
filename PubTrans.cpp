#include <bits/stdc++.h>
using namespace std;
using ll = long long;

string formatTime(double time);
class Station;
// ==================== Vehicle ====================
class Vehicle{
private:
protected:
    string type;
    string route;
    int capacity;
    int bookedSeats;
    string status;      //On-time / Delayed 
    int speed;
    double distance;   //km

public:
    Vehicle(string _type, string _route, int _capacity, int _bookedSeats, string _status, int _speed, double _distance){
        type = _type;
        route = _route;
        capacity = _capacity;
        bookedSeats = _bookedSeats;
        status = _status;
        speed = _speed;
        distance = _distance;
    }
    //Getter
    string getType(){return type;}
    string getRoute(){return route;}
    int getCapacity(){return capacity;}
    int getBookedSeats(){return bookedSeats;}
    string getStatus(){return status;}
    int getSpeed(){return speed;}
    double getDistance(){return distance;}
    //Setter
    void setType(string _type){type = _type;}
    void setRoute(string _route){route = _route;}
    void setCapacity(int _capacity){capacity = _capacity;}
    void setBookedSeats(int _bookedSeats){bookedSeats = _bookedSeats;}
    void setStatus(string _status){status = _status;}
    void setSpeed(int _speed){speed = _speed;}
    void setDistance(double _distance){distance = _distance;}

    bool bookSeat(){
        if(bookedSeats < capacity){
            bookedSeats++;
            return true;
        }
        return false;
    }

    void cancelSeat(){
        if(bookedSeats > 0) bookedSeats--;
    }

    virtual double calculateTravelTime(double distance){
        return distance / speed;
    }

    virtual void displayInfo() = 0;
    virtual void displaySummary() = 0;

    bool assignToStation(Station* st);


    virtual ~Vehicle(){}
};
// ==================== Bus ====================
class Bus : public Vehicle{
private:
protected:
public:
    Bus(string _route, int _capacity, int _bookedSeats, string _status, int _speed, double _distance) 
    : Vehicle("Bus", _route, _capacity, _bookedSeats, _status, _speed, _distance){}

    void displayInfo() override{
        cout << "[BUS] Route: " << getRoute() << endl;
        cout << "Capacity: " << getCapacity() << endl;
        cout << "Booked: " << getBookedSeats() << "/" << getCapacity() << endl;
        cout << "Status: " << getStatus() << endl;
        cout << "Speed: " << getSpeed() << " km/h" << endl;
    }

    void displaySummary() override{
    cout << "[" << getType() << "] " << getRoute() << " | Seats: " << getBookedSeats() << "/" << getCapacity() << " | Status: " << getStatus() << endl;
    }
};

// ==================== EcoBus ====================
class EcoBus : public Vehicle{
private:
protected:
public:
    EcoBus(string _route, int _capacity, int _bookedSeats, string _status, int _speed, double _distance) 
    : Vehicle("EcoBus", _route, _capacity, _bookedSeats, _status, _speed, _distance){}

    double calculateTravelTime(double distance) override{
        return (distance / speed) * 1.2;
    }
    
    void displayInfo() override{
        cout << "[ECO BUS] Route: " << getRoute() << endl;
        cout << "Capacity: " << getCapacity() << endl;
        cout << "Booked: " << getBookedSeats() << "/" << getCapacity() << endl;
        cout << "Status: " << getStatus() << endl;
        cout << "Speed: " << getSpeed() << " km/h" << endl;
    }

    void displaySummary() override{
    cout << "[" << getType() << "] " << getRoute() << " | Seats: " << getBookedSeats() << "/" << getCapacity() << " | Status: " << getStatus() << endl;
    }
};

// ==================== Train ====================
class Train : public Vehicle{
private:
protected:
public:
    Train(string _route, int _capacity, int _bookedSeats, string _status, int _speed, double _distance) 
    : Vehicle("Train", _route, _capacity, _bookedSeats, _status, _speed, _distance){}

    void displayInfo() override{
        cout << "[TRAIN] Route: " << getRoute() << endl;
        cout << "Capacity: " << getCapacity() << endl;
        cout << "Booked: " << getBookedSeats() << "/" << getCapacity() << endl;
        cout << "Status: " << getStatus() << endl;
        cout << "Speed: " << getSpeed() << " km/h" << endl;
    }

    void displaySummary() override{
    cout << "[" << getType() << "] " << getRoute() << " | Seats: " << getBookedSeats() << "/" << getCapacity() << " | Status: " << getStatus() << endl;
    }
};

// ==================== Metro ====================
class Metro : public Vehicle{
private:
protected:
public:
    Metro(string _route, int _capacity, int _bookedSeats, string _status, int _speed, double _distance) 
    : Vehicle("Metro", _route, _capacity, _bookedSeats, _status, _speed, _distance){}

    void displayInfo() override{
        cout << "[METRO] Route: " << getRoute() << endl;
        cout << "Capacity: " << getCapacity() << endl;
        cout << "Booked: " << getBookedSeats() << "/" << getCapacity() << endl;
        cout << "Status: " << getStatus() << endl;
        cout << "Speed: " << getSpeed() << " km/h" << endl;
    }

    void displaySummary() override{
    cout << "[" << getType() << "] " << getRoute() << " | Seats: " << getBookedSeats() << "/" << getCapacity() << " | Status: " << getStatus() << endl;
    }
};

// ==================== Schedule ====================
class Schedule{
private:
    string time;
    string status;          //Arriving / Departing
    Vehicle* vehicle;
protected:
public:
    Schedule(string _time, string _status, Vehicle* _vehicle){
        time = _time;
        status = _status;
        vehicle = _vehicle;
    }
    //Getter
    string getTime(){return time;}
    string getStatus(){return status;}
    Vehicle* getVehicle(){return vehicle;}
    //Setter
    void setTime(string _time){time = _time;}
    void setStatus(string _status){status = _status;}
    void setVehicle(Vehicle* _vehicle){vehicle = _vehicle;}

    void displayInfo(){
        if(vehicle){
        double travelTime = vehicle->calculateTravelTime(vehicle->getDistance());
        cout << "\t[" << getTime() << "] - " << vehicle->getType() << " from " << vehicle->getRoute() << " ---> " << vehicle->getStatus() << endl;
        cout << "\tEstimated arrival in " << formatTime(travelTime) << endl; 
        }
    }
};

// ==================== Station ====================
class Station{
private:
    string name;
    string location;
    string type;
    vector<Vehicle*> vehicles;
    vector<Schedule> schedules;
protected:
public:
    Station(string _name, string _location, string _type){
        name = _name;
        location = _location;
        type = _type;
    }
    //Getter
    string getName(){return name;}
    string getLocation(){return location;}
    string getType(){return type;}
    //Setter
    void setName(string _name){name = _name;}
    void setLocation(string _location){location = _location;}
    void setType(string _type){type = _type;}

    void addVehicle(Vehicle* _vehicle){
        vehicles.push_back(_vehicle);
    }

    void addSchedule(Schedule _schedule){
        schedules.push_back(_schedule);
    }

    void removeSchedule(int i){
        if(i >= 0 && i < schedules.size()){
            schedules.erase(schedules.begin() + i);
        }
    }

    void listSchedules(){
        for(int i=0; i<schedules.size(); i++){
            cout << "#" << i+1 << ". ";
            schedules[i].displayInfo();
        }
    }

    int getScheduleSize(){return schedules.size();}

    void displayInfo(){
        cout << "Station Name: " << getName() << endl;
        cout << "Location: " << getLocation() << endl;
        cout << "Type: " << getType() << endl;
    }

    void displaySummary(){
        cout << "[" << getType() << "] " << getName() << " (" << getLocation() << ")" << endl;
    }
    ~Station(){}
};

// ==================== Passenger ====================
class Passenger{
private:
    string name;
    int age;
    string ticketID;
    vector<Vehicle*> bookedVehicles;
protected:
public:
    Passenger(string _name, int _age, string _ticketID){
        name = _name;
        age = _age;
        ticketID = _ticketID;
    }
    //Getter
    string getName(){return name;}
    int getAge(){return age;}
    string getTicketID(){return ticketID;}
    //Setter
    void setName(string _name){name = _name;}
    void setAge(int _age){age = _age;}
    void setTicketID(string _ticketID){ticketID = _ticketID;}

    void displayInfo(){
        cout << "Passenger Name: " << getName() << endl;
        cout << "Age: " << getAge() << endl;
        cout << "Ticket ID: " << getTicketID() << endl;
        cout << "Booked Vehicles:" << endl;
        for(auto bv : bookedVehicles){
            bv->displayInfo();
            cout << "------------------------" << endl;
        }
    }

    void displaySummary(){
        cout << getName() << " (Age: " << getAge() << ", Ticket: " << getTicketID() << ")" << endl;
    }


    void bookTicket(Vehicle *_vehicle){
    // Kiểm tra đã đặt chưa
    bool alreadyBooked = false;
    for(int i = 0; i < bookedVehicles.size(); i++){
        if(bookedVehicles[i] == _vehicle){
            alreadyBooked = true;
            break;
            }
        }

    if(alreadyBooked){
        cout << getName() << " has already booked this vehicle!" << endl;
        return;
        }

    if(_vehicle->bookSeat()){
        bookedVehicles.push_back(_vehicle);
        cout << getName() << " successfully booked a seat on " << _vehicle->getRoute() << "." << endl;
        } else {
        cout << "Booking failed! No available seats." << endl;
        }
    }

    void cancelTicket(Vehicle *_vehicle){
    // tìm vị trí để xóa
    int pos = -1;
    for(int i = 0; i < bookedVehicles.size(); i++){
        if(bookedVehicles[i] == _vehicle){
            pos = i;
            break;
            }
        }

    if(pos == -1){
        cout << getName() << " has no booking for that vehicle." << endl;
        return;
        }

    bookedVehicles.erase(bookedVehicles.begin() + pos);
    _vehicle->cancelSeat();
    cout << getName() << " successfully canceled the ticket on " << _vehicle->getRoute() << "." << endl;
    } 
};

bool Vehicle::assignToStation(Station* st){
    if(st->getType() == type){
        st->addVehicle(this);
        return true;
    }
    return false;
}

// ==================== System ====================
class System{
private:
    vector<Station*> stations;
    vector<Passenger*> passengers;
    vector<Vehicle*> vehicles;
protected:
public:
    int getStationSize(){return stations.size();}
    int getPassengerSize(){return passengers.size();}
    int getVehicleSize(){return vehicles.size();}

    void addStation(Station* _station){
        stations.push_back(_station);
    }

    void addPassenger(Passenger* _passenger){
        passengers.push_back(_passenger);
    }
    void addVehicle(Vehicle* _vehicle){
        vehicles.push_back(_vehicle);
    }

    void displayStations(){
        cout << "\n==========List of Stations ==========" << endl;
        for(int i=0; i<stations.size(); i++){
            cout << "#" << i+1 << ". ";
            stations[i]->displayInfo();
            cout << endl;
        }
    }

    void displayPassengers(){
        cout << "\n==========List of Passengers ==========" << endl;
        for(int i=0; i<passengers.size(); i++){
            cout << "#" << i+1 << ". ";
            passengers[i]->displayInfo();
            cout << endl;
        }
    }

    void displayVehicles(){
        cout << "\n==========List of Vehicles ==========" << endl;
        for(int i=0; i<vehicles.size(); i++){
            cout << "#" << i+1 << ". ";
            vehicles[i]->displayInfo();
            cout << endl;
        }
    }

    void displayVehiclesSummary(){
    cout << "\n========== Vehicles ==========" << endl;
    for(int i=0; i<vehicles.size(); i++){
        cout << "#" << i+1 << ". ";
        vehicles[i]->displaySummary();
        }
    }

    void displayStationsSummary(){
    cout << "\n========== Stations ==========" << endl;
    for(int i=0; i<stations.size(); i++){
        cout << "#" << i+1 << ". ";
        stations[i]->displaySummary();
        }
    }

    void displayPassengersSummary(){
    cout << "\n========== Passengers ==========" << endl;
    for(int i=0; i<passengers.size(); i++){
        cout << "#" << i+1 << ". ";
        passengers[i]->displaySummary();
        }
    }

    Station* chooseStation(int i){
        if(i < 1 || i > stations.size()) return 0;
        return stations[i-1];
    }

    Passenger* choosePassenger(int i){
        if(i < 1 || i > passengers.size()) return 0;
        return passengers[i-1];
    }

    Vehicle* chooseVehicle(int i){
        if(i < 1 || i > vehicles.size()) return 0;
        return vehicles[i-1];
    }
    ~System(){
    for(auto v : vehicles) delete v;
    for(auto s : stations) delete s;
    for(auto p : passengers) delete p;
    }
};

// Hàm tạo mã vé ngẫu nhiên
string generateTicketID() {
    int num = rand() % 10000; // random từ 0 → 999
    stringstream ss;
    ss << "TICKET" << setw(4) << setfill('0') << num; 
    return ss.str();
}

// Hàm định dạng thời gian từ giờ thập phân sang giờ:phút
string formatTime(double time){
    int hours = (int)time;
    int minutes = (int)((time - hours) * 60);
    if(minutes == 60){
        hours++;
        minutes = 0;
    }
    stringstream ss;
    ss << hours << "h " << minutes << "m";
    return ss.str();
}

void menu(){
    cout << "========== Public Transportation Manager ==========" << endl;
    cout << "= = = = = Station Permissions = = = = = =" << endl;
    cout << "1. Add a new station" << endl;
    cout << "2. Add a new schedule" << endl;
    cout << "3. Remove a new schedule" << endl;
    cout << "4. Show list of scheduled arrivals/departures" << endl;
    cout << "= = = = = Vehicle Permissions = = = = = =" << endl;
    cout << "5. Add a new vehicle" << endl;
    cout << "6. Assign the vehicle to the station" << endl;
    cout << "= = = = = Passenger Permissions = = = = = =" << endl;
    cout << "7. Add a new passenger" << endl;
    cout << "8. Book a ticket" << endl;
    cout << "9. Cancel a ticket" << endl;
    cout << "= = = = = System Permissions = = = = = =" << endl;
    cout << "10. Show list of stations" << endl;
    cout << "11. Show list of vehicles" << endl;
    cout << "12. Show list of passengers" << endl;
    cout << "= = = = = = = = = = = = = =" << endl;
    cout << "0. Exit the Public Transportation Manager" << endl;
    cout << "====================================" << endl;
    cout << "Choose your choice: ";
}

int main(){
    System sys;
    int choice;
    //Tạo sẵn station mẫu
    Station* busStation = new Station("Ben Xe An Suong", "TP.HCM", "Bus");
    Station* ecoBusStation = new Station("Ben Xe Thao Dien", "TP.HCM", "EcoBus");
    Station* trainStation = new Station("Ga Sai Gon", "TPHCM", "Train");
    Station* metroStation = new Station("Ga Ben Thanh", "TP.HCM", "Metro");
    //Tạo sẵn vehicle mẫu
    Vehicle* bus1 = new Bus("District 12 -> Tan Binh District", 30, 10, "On-time", 55, 14);
    Vehicle* bus2 = new Bus("District 12 - > District 1", 40, 25, "Delayed", 60, 17.7);

    Vehicle* eco1 = new EcoBus("District 2 -> District 7", 35, 25, "Delayed", 40, 11.1);
    Vehicle* eco2 = new EcoBus("District 2 -> Thu Duc City", 50, 45, "On-time", 45, 8.5);

    Vehicle* train1 = new Train("HCM -> Da Nang", 200, 150, "On-time", 120, 935);
    Vehicle* train2 = new Train("HCM -> Phan Thiet", 180, 160, "Delayed", 110, 187);

    Vehicle* metro1 = new Metro("Ben Thanh -> Suoi Tien", 300, 200, "On-time", 135, 19.7);
    Vehicle* metro2 = new Metro("Ben Thanh -> Thao Dien", 250, 180, "On-time", 120, 11.3);

    //Gán vehicle vào station
    bus1->assignToStation(busStation);
    bus2->assignToStation(busStation);
    eco1->assignToStation(ecoBusStation);
    eco2->assignToStation(ecoBusStation);
    train1->assignToStation(trainStation);
    train2->assignToStation(trainStation);
    metro1->assignToStation(metroStation);
    metro2->assignToStation(metroStation);

    //Thêm lịch trình mẫu
    Schedule sch1("08:00", "Arriving", bus1);
    Schedule sch2("09:00", "Departing", bus2);
    Schedule sch3("10:00", "Arriving", eco1);
    Schedule sch4("11:00", "Departing", eco2);
    Schedule sch5("12:00", "Arriving", train1);
    Schedule sch6("13:00", "Departing", train2);
    Schedule sch7("14:00", "Arriving", metro1);
    Schedule sch8("15:00", "Departing", metro2);

    //Tạo sẵn passenger mẫu
    Passenger* p1 = new Passenger("Nguyen Khanh Bang", 19, "TICKET0001");
    Passenger* p2 = new Passenger("Nguyen Vu Nhat Duy", 19, "TICKET0002");
    Passenger* p3 = new Passenger("Nguyen Khanh Tuyet", 7, "TICKET0003");

    //Thêm vào hệ thống
    sys.addStation(busStation);
    sys.addStation(ecoBusStation);
    sys.addStation(trainStation);
    sys.addStation(metroStation);

    sys.addVehicle(bus1);
    sys.addVehicle(bus2);
    sys.addVehicle(eco1);
    sys.addVehicle(eco2);
    sys.addVehicle(train1);
    sys.addVehicle(train2);
    sys.addVehicle(metro1);
    sys.addVehicle(metro2);

    sys.addPassenger(p1);
    sys.addPassenger(p2);
    sys.addPassenger(p3);

    //Main menu
    while(true){
        menu();
        cin >> choice; cin.ignore();

        //OPTION 1: Add a new station
        if(choice == 1){
            string _name, _location, _type;
            cout << "Enter station name: "; getline(cin, _name);
            cout << "Enter station location: "; getline(cin, _location);
            cout << "Enter station type: " << endl;
            cout << "\t#1. Bus" << endl;
            cout << "\t#2. EcoBus" << endl;
            cout << "\t#3. Train" << endl;
            cout << "\t#4. Metro" << endl;
            cout << "Choose your option: ";
            int tChoice; cin >> tChoice;
            while (cin.fail() || tChoice < 0){ // kiểm tra nhập đúng số nguyên dương
                cout << "Invalid input...!!! Please enter a non-negative number: ";
                cin.clear();
                cin.ignore(10000,'\n');
                cin >> tChoice;
            }
            cin.ignore();
            if(tChoice == 1) _type = "Bus";
            else if(tChoice == 2) _type = "EcoBus";
            else if(tChoice == 3) _type = "Train";
            else if(tChoice == 4) _type = "Metro";
            else {
                cout << "Invalid type choice...!" << endl;
                continue;
            } 
            Station* st = new Station(_name, _location, _type);
            sys.addStation(st);
            cout << "Station added successfully...!" << endl;
        }

        //OPTION 2: Add a new schedule
        else if(choice == 2){
            if(sys.getStationSize() == 0){
                cout << "No stations available. Please add a station first." << endl;
                continue;
            }

            cout << "Select a station to add schedule:" << endl;
            sys.displayStationsSummary();
            cout << "Enter station number: ";
            int sChoice; cin >> sChoice;
            while (cin.fail() || sChoice < 0){ // kiểm tra nhập đúng số nguyên dương
                cout << "Invalid input...!!! Please enter a non-negative number: ";
                cin.clear();
                cin.ignore(10000,'\n');
                cin >> sChoice;
            }
            cin.ignore();
            Station* chosenStation = sys.chooseStation(sChoice);
            if(!chosenStation){
                cout << "Invalid station choice...!" << endl;
                continue;
            }

            cout << "Select a vehicle to schedule:" << endl;
            sys.displayVehiclesSummary();
            cout << "Enter vehicle number: ";
            int vChoice; cin >> vChoice;
            while (cin.fail() || vChoice < 0){ // kiểm tra nhập đúng số nguyên dương
                cout << "Invalid input...!!! Please enter a non-negative number: ";
                cin.clear();
                cin.ignore(10000,'\n');
                cin >> vChoice;
            }
            cin.ignore();
            Vehicle* chosenVehicle = sys.chooseVehicle(vChoice);
            if(!chosenVehicle){
                cout << "Invalid vehicle choice...!" << endl;
                continue;
            }

            if (chosenStation->getType() != chosenVehicle->getType()) {
            cout << "Error: Cannot schedule a " << chosenVehicle->getType()
            << " at a " << chosenStation->getType() << " station!" << endl;
            continue;
            }

            string _time, _status;
            cout << "Enter schedule time (hour:minute): "; getline(cin, _time);
            cout << "Enter schedule status (Arriving/Departing): "; getline(cin, _status);
            Schedule sch(_time, _status, chosenVehicle);
            chosenStation->addSchedule(sch);
            cout << "Schedule added successfully...!" << endl;
        }

        //OPTION 3: Remove a schedule
        else if(choice == 3){
            if(sys.getStationSize() == 0){
                cout << "No stations available. Please add a station first." << endl;
                continue;
            }

            cout << "Select a station to remove schedule:" << endl;
            sys.displayStationsSummary();
            cout << "Enter station number: ";
            int sChoice; cin >> sChoice;
            while (cin.fail() || sChoice < 0){ // kiểm tra nhập đúng số nguyên dương
                cout << "Invalid input...!!! Please enter a non-negative number: ";
                cin.clear();
                cin.ignore(10000,'\n');
                cin >> sChoice;
            }
            cin.ignore();
            Station* chosenStation = sys.chooseStation(sChoice);
            if(!chosenStation){
                cout << "Invalid station choice...!" << endl;
                continue;
            }

            cout << "Schedules at this station:" << endl;
            chosenStation->listSchedules();

            if(chosenStation->getScheduleSize() == 0){
                cout << "No schedules available to remove." << endl;
                continue;
            }

            cout << "Enter schedule number to remove: ";
            int sPos; cin >> sPos;
            while (cin.fail() || sPos < 0){ // kiểm tra nhập đúng số nguyên dương
                cout << "Invalid input...!!! Please enter a non-negative number: ";
                cin.clear();
                cin.ignore(10000,'\n');
                cin >> sPos;
            }
            cin.ignore();

            if(sPos < 1){
                cout << "Invalid schedule choice...!" << endl;
                continue;
            }
            chosenStation->removeSchedule(sPos - 1);
            cout << "Schedule removed successfully...!" << endl;
        }

        //OPTION 4: Show list of scheduled arrivals/departures
        else if(choice == 4){
            if(sys.getStationSize() == 0){
                cout << "No stations available. Please add a station first." << endl;
                continue;
            }

            cout << "Select a station to view schedules:" << endl;
            sys.displayStations();
            cout << "Enter station number: ";
            int sChoice; cin >> sChoice;
            while (cin.fail()|| sChoice < 0){ // kiểm tra nhập đúng số nguyên dương
                cout << "Invalid input...!!! Please enter a non-negative number: ";
                cin.clear();
                cin.ignore(10000,'\n');
                cin >> sChoice;
            }
            cin.ignore();
            Station* chosenStation = sys.chooseStation(sChoice);
            if(!chosenStation){
                cout << "Invalid station choice...!" << endl;
                continue;
            }

            cout << "Schedules at " << chosenStation->getName() << ":" << endl;
            chosenStation->listSchedules();
            if(chosenStation->getScheduleSize() == 0){
                cout << "No schedules available...!" << endl;
            }
        }

        //OPTION 5: Add a new vehicle
        else if(choice == 5){
            string _route, _status, _type;
            int _capacity, _bookedSeats, _speed;
            cout << "Enter vehicle type: " << endl;
            cout << "\t#1. Bus" << endl;
            cout << "\t#2. EcoBus" << endl;
            cout << "\t#3. Train" << endl;
            cout << "\t#4. Metro" << endl;
            cout << "Choose your option: ";
            int tChoice; cin >> tChoice;
            while (cin.fail() || tChoice < 0){ // kiểm tra nhập đúng số nguyên dương
                cout << "Invalid input...!!! Please enter a non-negative number: ";
                cin.clear();
                cin.ignore(10000,'\n');
                cin >> tChoice;
            }
            cin.ignore();
            if(tChoice == 1) _type = "Bus";
            else if(tChoice == 2) _type = "EcoBus";
            else if(tChoice == 3) _type = "Train";
            else if(tChoice == 4) _type = "Metro";
            else {
                cout << "Invalid type choice...!" << endl;
                continue;
            }
            cout << "Enter vehicle route: "; getline(cin, _route);
            cout << "Enter vehicle capacity: "; cin >> _capacity;
            while (cin.fail() || _capacity < 0){ // kiểm tra nhập đúng số nguyên dương
                cout << "Invalid input...!!! Please enter a non-negative number: ";
                cin.clear();
                cin.ignore(10000,'\n');
                cin >> _capacity;
            }
            cin.ignore();
            cout << "Enter booked seats: "; cin >> _bookedSeats;
            while (cin.fail() || _bookedSeats < 0){ // kiểm tra nhập đúng số nguyên dương
                cout << "Invalid input...!!! Please enter a non-negative number: ";
                cin.clear();
                cin.ignore(10000,'\n');
                cin >> _bookedSeats;
            }
            cin.ignore();
            cout << "Enter vehicle speed (km/h): "; cin >> _speed;
            while (cin.fail() || _speed < 0){ // kiểm tra nhập đúng số nguyên dương
                cout << "Invalid input...!!! Please enter a non-negative number: ";
                cin.clear();
                cin.ignore(10000,'\n');
                cin >> _speed;
            }
            cin.ignore();
            cout << "Enter vehicle status (On-time/Delayed): "; getline(cin, _status);
            cout << "Enter travel distance (km): "; double _distance; cin >> _distance;
            while (cin.fail() || _distance < 0){ // kiểm tra nhập đúng số nguyên dương
                cout << "Invalid input...!!! Please enter a non-negative number: ";
                cin.clear();
                cin.ignore(10000,'\n');
                cin >> _distance;
            }
            cin.ignore();

            Vehicle* _vehicle = nullptr;
            if(_type == "Bus") _vehicle = new Bus(_route, _capacity, _bookedSeats, _status, _speed, _distance);
            else if(_type == "EcoBus") _vehicle = new EcoBus(_route, _capacity, _bookedSeats, _status, _speed, _distance);
            else if(_type == "Train") _vehicle = new Train(_route, _capacity, _bookedSeats, _status, _speed, _distance);
            else if(_type == "Metro") _vehicle = new Metro(_route, _capacity, _bookedSeats, _status, _speed, _distance);
            sys.addVehicle(_vehicle);
            cout << "Vehicle added successfully...!" << endl;
        }

        //OPTION 6: Assign the vehicle to the station
        else if(choice == 6){
            if(sys.getStationSize() == 0){
                cout << "No stations available. Please add a station first." << endl;
                continue;
            }
            if(sys.getVehicleSize() == 0){
                cout << "No vehicles available. Please add a vehicle first." << endl;
                continue;
            }

            cout << "Select a station to assign vehicle:" << endl;
            sys.displayStationsSummary();
            cout << "Enter station number: ";
            int sChoice; cin >> sChoice;
            while (cin.fail() || sChoice < 0){ // kiểm tra nhập đúng số nguyên dương
                cout << "Invalid input...!!! Please enter a non-negative number: ";
                cin.clear();
                cin.ignore(10000,'\n');
                cin >> sChoice;
            }
            cin.ignore();
            Station* chosenStation = sys.chooseStation(sChoice);
            if(!chosenStation){
                cout << "Invalid station choice...!" << endl;
                continue;
            }

            cout << "Select a vehicle to assign:" << endl;
            sys.displayVehiclesSummary();
            cout << "Enter vehicle number: ";
            int vChoice; cin >> vChoice;
            while (cin.fail() || vChoice < 0){ // kiểm tra nhập đúng số nguyên dương
                cout << "Invalid input...!!! Please enter a non-negative number: ";
                cin.clear();
                cin.ignore(10000,'\n');
                cin >> vChoice;
            }
            cin.ignore();
            Vehicle* chosenVehicle = sys.chooseVehicle(vChoice);
            if(!chosenVehicle){
                cout << "Invalid vehicle choice...!" << endl;
                continue;
            }

            if(chosenVehicle->assignToStation(chosenStation)){
                cout << "Vehicle assigned to station successfully...!" << endl;
            }else{
                cout << "Failed: " << chosenVehicle->getType()
                    << " cannot be assigned to station of type "
                    << chosenStation->getType() << endl;
            }
        }

        //OPTION 7: Add a new passenger
        else if(choice == 7){
            string _name;
            int _age;
            cout << "Enter passenger name: "; getline(cin, _name);
            cout << "Enter passenger age: "; cin >> _age;
            while (cin.fail() || _age < 0){ // kiểm tra nhập đúng số nguyên dương
                cout << "Invalid input...!!! Please enter a non-negative number: ";
                cin.clear();
                cin.ignore(10000,'\n');
                cin >> _age;
            }
            cin.ignore();
            string _ticketID = generateTicketID();
            Passenger* p = new Passenger(_name, _age, _ticketID);
            sys.addPassenger(p);
            cout << "Passenger added successfully...!" << endl;
            cout << "Generated Ticket ID: " << _ticketID << endl;
        }

        //OPTION 8: Book a ticket
        else if(choice == 8){
            if(sys.getPassengerSize() == 0){
                cout << "No passengers available. Please add a passenger first." << endl;
                continue;
            }
            if(sys.getVehicleSize() == 0){
                cout << "No vehicles available. Please add a vehicle first." << endl;
                continue;
            }

            cout << "Select a passenger to book ticket:" << endl;
            sys.displayPassengersSummary();
            cout << "Enter passenger number: ";
            int pChoice; cin >> pChoice;
            while (cin.fail() || pChoice < 0){ // kiểm tra nhập đúng số nguyên dương
                cout << "Invalid input...!!! Please enter a non-negative number: ";
                cin.clear();
                cin.ignore(10000,'\n');
                cin >> pChoice;
            }
            cin.ignore();
            Passenger* chosenPassenger = sys.choosePassenger(pChoice);
            if(!chosenPassenger){
                cout << "Invalid passenger choice...!" << endl;
                continue;
            }

            cout << "Select a vehicle to book ticket:" << endl;
            sys.displayVehiclesSummary();
            cout << "Enter vehicle number: ";
            int vChoice; cin >> vChoice;
            while (cin.fail() || vChoice < 0){ // kiểm tra nhập đúng số nguyên dương
                cout << "Invalid input...!!! Please enter a non-negative number: ";
                cin.clear();
                cin.ignore(10000,'\n');
                cin >> vChoice;
            }
            cin.ignore();
            Vehicle* chosenVehicle = sys.chooseVehicle(vChoice);
            if(!chosenVehicle){
                cout << "Invalid vehicle choice...!" << endl;
                continue;
            }

            chosenPassenger->bookTicket(chosenVehicle);
        }

        //OPTION 9: Cancel a ticket
        else if(choice == 9){
            if(sys.getPassengerSize() == 0){
                cout << "No passengers available. Please add a passenger first." << endl;
                continue;
            }
            if(sys.getVehicleSize() == 0){
                cout << "No vehicles available. Please add a vehicle first." << endl;
                continue;
            }

            cout << "Select a passenger to cancel ticket:" << endl;
            sys.displayPassengersSummary();
            cout << "Enter passenger number: ";
            int pChoice; cin >> pChoice;
            while (cin.fail() || pChoice < 0){ // kiểm tra nhập đúng số nguyên dương
                cout << "Invalid input...!!! Please enter a non-negative number: ";
                cin.clear();
                cin.ignore(10000,'\n');
                cin >> pChoice;
            }
            cin.ignore();
            Passenger* chosenPassenger = sys.choosePassenger(pChoice);
            if(!chosenPassenger){
                cout << "Invalid passenger choice...!" << endl;
                continue;
            }

            cout << "Select a vehicle to cancel ticket:" << endl;
            sys.displayVehiclesSummary();
            cout << "Enter vehicle number: ";
            int vChoice; cin >> vChoice;
            while (cin.fail() || vChoice < 0){ // kiểm tra nhập đúng số nguyên dương
                cout << "Invalid input...!!! Please enter a non-negative number: ";
                cin.clear();
                cin.ignore(10000,'\n');
                cin >> vChoice;
            }
            cin.ignore();
            Vehicle* chosenVehicle = sys.chooseVehicle(vChoice);
            if(!chosenVehicle){
                cout << "Invalid vehicle choice...!" << endl;
                continue;
            }

            chosenPassenger->cancelTicket(chosenVehicle);
        }

        //OPTION 10: Show list of stations
        else if(choice == 10){
            sys.displayStations();
        }

        //OPTION 11: Show list of vehicles
        else if (choice == 11) {
            sys.displayVehicles();
        }

        //OPTION 12: Show list of passengers
        else if (choice == 12) {
            sys.displayPassengers();
        }
        
        //OPTION 0: Exit the public transportation manager
        else if (choice == 0) {
            cout << "Exiting the Public Transportation Manager. Goodbye!" << endl;
            break;
        }

        //Inappropriate choice
        else {
            cout << "Invalid choice. Please try again." << endl;
        }

        system("pause");
        system("cls");
    }
}

