#include <bits/stdc++.h> 
#include <vector>
#include <algorithm>
#include <yaml-cpp/yaml.h>
#include <exception>
using namespace std;


// Add constructor and destructor 
class ReadYAML{

    private:
	    unsigned int i;
    public:
    	unsigned int bridgesCount;
    	vector<float> bridgesLength;
    	vector<float> personSpeed;
	vector<unsigned int> personPosition;
	int readYaml();
	ReadYAML();        //Constructor decalaration
	~ReadYAML();       //destructor decalaration
	

};

// Member functions definitions including constructor
ReadYAML::ReadYAML(void) {
   cout << "Object for ReadYAML is being created" << endl;
}
ReadYAML::~ReadYAML(void) {
   cout << "Object for ReadYAML is being deleted" << endl;
}

//handle if the person list is empty or negative
//handle if the bridge count is empty or negative
//handle if the person speed is empty or negative
//handle if the person position is empty or negative
int ReadYAML::readYaml(){
	YAML::Node usrInp = YAML::LoadFile("userInp.yaml"); //Load the Yaml file

        try{
            bridgesCount = usrInp["bridges"].as<unsigned int>();
	    bridgesLength = usrInp["length"].as<vector<float>>();
            personSpeed = usrInp["personsSpeed"].as<vector<float>>();
            personPosition = usrInp["personsPosition"].as<vector<unsigned int>>();
	    if(bridgesLength.empty() || personSpeed.empty() || personPosition.empty()){
                cout<<"Error:Yaml file empty data"<<endl;
		return 0;
	    }
	    if( (bridgesCount != bridgesLength.size()) || (personSpeed.size() != (personPosition.size()))){
		cout<<"Error:User data is not Valid"<<endl;
		return 0;
             }

	     if (bridgesCount < 1){
		cout<<"Error:Bridge data must be positive integers"<<endl;
                return 0;


             }
	     for(i = 0; i < bridgesLength.size(); i++){
                 if(bridgesLength[i] < 0){
			cout<<"Error:Bridge data must be positive integers"<<endl;
                        return 0;
		 }
	     }
	     for(i = 0; i < personSpeed.size(); i++){
                 if((personSpeed[i] < 0) || (personPosition[i] < 0)){
                        cout<<"Error:Person data must be positive integers"<<endl;
                        return 0;
                 }
             }


        }
        catch (exception& e){
            cout << "Error:Yaml file reading Error: " << e.what() << endl;
            return 0;
        }
        return 1; 
}

//add constructor and destructor.
//the time taken should be variable of a class. 
class CrossingBridge{

	private:
		float totalTimeTaken ;

	public:
                
		int status = 0;
	        ReadYAML objectYaml;		
		float getMinimumTime();
		int get_minimum_crossing_time(unsigned int,vector<float> );
		CrossingBridge(float time);  //Created Crossing Bridge object constructor

};

// Member functions definitions including constructor
CrossingBridge::CrossingBridge( float time) {
   totalTimeTaken = time;
}
//return time based on person speed read from YAML file 
float CrossingBridge::getMinimumTime(){

        unsigned int i,j,cnt;
        status = objectYaml.readYaml();
	if (status == 0 ){
            return 0;
        }	
        cnt = 0;
        for(i = 0; i < objectYaml.bridgesCount; i++) {
                
                for(j=0; j<objectYaml.personSpeed.size(); j++)
                {
                      if(objectYaml.personPosition[j] == (i+1)){
                       cnt = cnt + 1;
                  }
                }
                vector<float> person_walkingTime(cnt);

                   
                //Sort the personSpped in descending Order
                sort(objectYaml.personSpeed.begin(),objectYaml.personSpeed.begin()+cnt,greater<float>());

                //Calculate time of each person
                for(j=0;j<cnt;j++)
                {
		    person_walkingTime[j] = objectYaml.bridgesLength[i]/objectYaml.personSpeed[j];
                }
                
                totalTimeTaken = get_minimum_crossing_time(cnt,person_walkingTime) + totalTimeTaken;
        }
	return totalTimeTaken;

}

//return min bridge crossing time for n person(s)
//handle special cases if n = 0, n =1 , n =2, n = 3  
//handle special case if vector of person is not valid
int CrossingBridge::get_minimum_crossing_time(unsigned int n,vector<float> person_walkingTime)
{
    if (n == 0)
    {
        return 0;
    }
    
    if (n < 3)
    {
	return person_walkingTime.back();
    }
    else if (n == 3)
    {
        // Person 0 and 1 cross from A to B
        // Person 0 crosses back to A
        // Person 0 and 2 cross from A to B
	return person_walkingTime[1] + person_walkingTime[0] + person_walkingTime[2];
    }
    float time_taken = 0;

    // Person 0 and Person 1 cross from A to B
    time_taken += person_walkingTime[1];

    // Person 1 crosses back to A
    time_taken += person_walkingTime[1];

    // Person (n-2) and Person (n-1) cross from A to B
    time_taken += person_walkingTime[n-1];

    // Person 0 goes back and forth to escort everyone else
    for (unsigned int i = 1; i < n-2; ++i)
    {
        // Person 0 crosses back to A
	time_taken += person_walkingTime[0];

        // Person 0 and Person i cross from A to B
	time_taken += person_walkingTime[i];
    }

    return time_taken;
}


/*int main(void)
{
	
        //Create object to get the time taken to cross the bridge
	CrossingBridge getTime(0.0);
	float totalTimeTaken = getTime.getMinimumTime();
	printf("The Minimum crossing time: %f\n",totalTimeTaken);
	return 0;
	
}*/
