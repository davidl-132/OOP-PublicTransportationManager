# Public Transportation Management System – OOP Assignment  

## 📌 Overview  

- `PubTrans.cpp` – A **Public Transportation Management System** built with **Object-Oriented Programming (OOP) in C++**.  
- The system manages:  
  - **Stations** (Bus, EcoBus, Train, Metro)  
  - **Vehicles** (Bus, EcoBus, Train, Metro)  
  - **Passengers** (with booking and cancellation features)  
  - **Schedules** (arrivals and departures)  
- Demonstrates **encapsulation, inheritance, polymorphism, and abstraction** in a real-world transportation scenario in Vietnam.  

---  

## ⚙️ Build & Run Instructions  

### On Linux / macOS / WSL:  

```bash
g++ PubTrans.cpp -o pubtrans
./pubtrans
```

### On Windows (MinGW g++):  

```bash
g++ PubTrans.cpp -o pubtrans.exe
pubtrans.exe
```

---  

## 🧩 Features  

- Add, remove, and list **Stations**.  
- Add and assign **Vehicles** to stations.  
- Create, remove, and display **Schedules** for arrivals and departures.  
- Register **Passengers** with generated ticket IDs.  
- Book and cancel **Tickets** for vehicles.  
- Prevents booking when a vehicle is at **full capacity**.  
- Prevents assigning a vehicle to the **wrong type of station** (e.g., Bus → Train Station).  
- Supports displaying **summaries** of all stations, vehicles, passengers, and schedules.  
- Calculates **estimated travel time** based on distance and vehicle speed (EcoBus adds 20% longer travel time).  

---  

## 🤖 AI Disclosure  

- Author: **Ly Tran Gia Khang – 24110098**  
- Used **ChatGPT** for:  
  - Brainstorming inheritance hierarchy (Vehicle → Bus, EcoBus, Train, Metro).  
  - Suggestions for input validation and menu-driven interface.  
  - Guidance on formatting travel time and preventing invalid bookings.  
- All code was **implemented, tested, and customized** before submission.  

---  

## 📝 Reflection  

This project gave me practical experience with **OOP principles** applied to a **real-world transportation system in Vietnam**.  

- Using a base class `Vehicle` and derived classes (`Bus`, `EcoBus`, `Train`, `Metro`) helped me understand **inheritance and polymorphism**.  
- Overriding `calculateTravelTime()` in `EcoBus` demonstrated how specialized vehicles behave differently.  
- Implementing **booking/cancellation** taught me how to manage dynamic relationships between objects (Passenger ↔ Vehicle).  
- Handling **capacity limits, schedule management, and input validation** made the system more realistic.  

Challenges included ensuring **type safety when assigning vehicles to stations**, and designing schedules without conflicts. Future improvements could include:  
- Better **time conflict management** in schedules.  
- Adding **data persistence** (saving to files or databases).  
- Extending with more vehicle types or multi-city management.  

This assignment improved my ability to design and implement **scalable OOP applications** for real-world use cases.  
