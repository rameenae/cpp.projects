//        WASTE MANAGEMENT SYSTEM


#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class WasteSchedule {
private:
    int currentDay;
    int intervalDays;
public:
    WasteSchedule(int startDay = 1, int interval = 3) : currentDay(startDay), intervalDays(interval) 
	{}

    bool isPickupDay() const 
	{return(currentDay % intervalDays)== 0; 
	}

    void nextDay(){
	 currentDay++; }

    int getCurrentDay() const { 
	return currentDay; }

    void setInterval(int interval)
	{
        if (interval>0) intervalDays=interval;
    }

    int getInterval() const 
	{ return intervalDays;
	 }
};
class Bin {
protected:
    int capacity;
    int fillLevel;
public:
    Bin(int cap):capacity(cap), fillLevel(0)
	 {}

    void setFillLevel(int level)
	{
        if (level<0) fillLevel = 0;
        else if (level>capacity) fillLevel = capacity;
        else fillLevel =level;
    }
    int getFillLevel() const {
	 return fillLevel; }

    bool isFull() const {
	 return fillLevel>=capacity; }

    virtual bool isHazardous() const {
	 return false; }

    void empty()
	 { fillLevel = 0; 
	 }

    int getCapacity() const 
	{ return capacity;
	 }
};
class HazardousBin :public Bin {
private:
    int priority;
public:
    HazardousBin(int cap, int prio) :Bin(cap), priority(prio)
	 {}

    int getPriority() const
	 { return priority; 
	 }

    bool isHazardous() const override { return true; }
};
class Logger{
private:
    ofstream logfile;

public:
    Logger(const string& filename) {
        logfile.open(filename, ios::app);
        if (!logfile.is_open()) {
            cerr << "Warning: could not open log file: " << filename << endl;
        }
    }
    ~Logger() {
        if (logfile.is_open()) logfile.close();
    }
    void log(const string& entry)
	 {
        if (logfile.is_open()){
            logfile<<entry<<endl;
        }}
    
};

class WasteManager {
private:
    Bin** bins;
    int binCount;
    WasteSchedule schedule;
    Logger logger;
public:
    WasteManager(Bin** binsArray, int count, WasteSchedule sched, const string& logFilename): bins(binsArray), binCount(count), schedule(sched), logger(logFilename) {}

    void updateBinFillLevelsFromUser() {
        for (int i = 0; i < binCount; ++i) {
            int level;
            while (true) {
                cout << "Enter fill level for bin " << (i + 1);
                if (bins[i]->isHazardous()) cout << " (Hazardous)";
                cout << " [0-" << bins[i]->getCapacity() << "]: ";
                cin >> level;

                if (!cin.fail()&&level>=0 && level<=bins[i]->getCapacity())
				 {
                    bins[i]->setFillLevel(bins[i]->getFillLevel()+level);
                    break;
                }
                cin.clear();
                cin.ignore(10000, '\n'); 
                cout << "Invalid input. Please enter a number between 0 and " << bins[i]->getCapacity() << "." << endl;
            }}}

    void printBinStatus() {
        cout<<"Bin Status:"<<endl;
        for(int i = 0;i < binCount;i++){
            cout<< "  Bin " <<(i + 1);
            if (bins[i]->isHazardous()) cout<<" (Hazardous)";
            cout<<": "<< bins[i]->getFillLevel() << "/" << bins[i]->getCapacity();
            if (bins[i]->isFull()) cout << " (Full)";
            cout<<endl;
        }}
    void simulateDay() {
        logger.log("Day " + to_string(schedule.getCurrentDay()));

        if (schedule.getCurrentDay()%3== 0){
            cout<<"Day "<<schedule.getCurrentDay()<<": Waste Pickup Scheduled (all bins). Emptying all bins."<<endl;
            logger.log("Pickup scheduled for all bins.");
            for(int i=0;i<binCount;i++){
                bins[i]->empty();
                cout<<"Emptied Bin "<<(i + 1);
                if (bins[i]->isHazardous())cout<<" (Hazardous)";
                cout<< "." <<endl;
                logger.log("Bin " +to_string(i + 1)+(bins[i]->isHazardous() ? " (Hazardous)" : "") + " emptied.");
            }
        } else {
            bool hazardousFull = false;
            for(int i=0;i<binCount;i++) {
                HazardousBin* hbin = dynamic_cast<HazardousBin*>(bins[i]);
                if (hbin && hbin->isFull()) {
                    hazardousFull = true;
                    break;
                }
            }
            if (hazardousFull)
                schedule.setInterval(1);
            else {
                bool anyFull = false;
                for (int i = 0; i < binCount; i++) {
                    if (bins[i]->isFull()) {
                        anyFull = true;
                        break;
                    }
                }
                schedule.setInterval(anyFull ? 2 : 3);
            }

            cout << "Waste collection interval currently set to every " << schedule.getInterval() << " day(s)." << endl;
            if (schedule.isPickupDay()) {
                cout << "Day " << schedule.getCurrentDay() << ": Waste Pickup Scheduled. Emptying full bins." << endl;
                logger.log("Pickup scheduled.");
                for (int i = 0; i < binCount; i++) {
                    if (bins[i]->isFull()) {
                        bins[i]->empty();
                        cout << "Emptied Bin " << (i + 1);
                        if (bins[i]->isHazardous()) cout << " (Hazardous)";
                        cout << "." << endl;
                        logger.log("Bin " + to_string(i + 1) + (bins[i]->isHazardous() ? " (Hazardous)" : "") + " emptied.");
                    }
                }
            } else {
                cout << "Day " << schedule.getCurrentDay() << ": No Pickup Today." << endl;
                logger.log("No pickup today.");
            }
        }

        printBinStatus();

        schedule.nextDay();
        cout << endl;
    }
};

int main() {
    const int numberOfBins = 4;
    Bin*bins[numberOfBins];
    bins[0]= new Bin(5);
    bins[1]= new HazardousBin(5, 10);
    bins[2]= new Bin(5);
    bins[3]= new HazardousBin(5, 5);
    WasteSchedule schedule(1, 3);
    WasteManager manager(bins, numberOfBins, schedule, "Waste_Bin.txt");
    const int simulationDays = 10;
    cout<<"***********WASTE MANAGEMENT SYSTEM***********\n";
    for (int day = 0; day < simulationDays; ++day) {
        cout << "=== Day " << (day + 1) << " ===" << endl;
        manager.updateBinFillLevelsFromUser();
        manager.simulateDay();
    }

    for (int i = 0; i < numberOfBins; ++i) {
        delete bins[i];
    }

    cout << "Simulation complete. Events logged to waste_log.txt" << endl;
    return 0;
}
