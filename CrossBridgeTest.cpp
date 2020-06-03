#include <bits/stdc++.h> 
#include <vector>
#include <algorithm>
#include <yaml-cpp/yaml.h>
#include <exception>
using namespace std;

//may be create a hikers class 
struct Person
{
    float walking_time;
};

// Add constructor and destructor 
class ReadYAML{

    private:
	    int i;
    public:
    	int bridgesCount;
    	vector<float> bridgesLength;
    	vector<float> personSpeed;
	vector<int> personPosition;
	int readYaml();
	

};

//handle if the person list is empty or negative
//handle if the bridge count is empty or negative
//handle if the person speed is empty or negative
//handle if the person position is empty or negative
int ReadYAML::readYaml(){
	YAML::Node usrInp = YAML::LoadFile("userInp.yaml"); //Load the Yaml file

        try{
            bridgesCount = usrInp["bridges"].as<int>();
	    bridgesLength = usrInp["length"].as<vector<float>>();
            personSpeed = usrInp["personsSpeed"].as<vector<float>>();
            personPosition = usrInp["personsPosition"].as<vector<int>>();
	    if(bridgesLength.empty() || personSpeed.empty() || personPosition.empty()){
                cout<<"Error:Yaml file empty data"<<endl;
		return 0;
	    }
	    if( (bridgesCount != bridgesLength.size()) || (personSpeed.size() != (personPosition.size()))){
		cout<<"Error:User data is not Valied"<<endl;
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

	public:
                ReadYAML objectYaml;		
		int status = objectYaml.readYaml();
		float getMinimumTime();
		unsigned int get_minimum_crossing_time(unsigned int ,vector<Person> );

};
//return time based on person speed read from YAML file 
float CrossingBridge::getMinimumTime(){

        int i,j,cnt;
	float totalTimeTaken = 0;
        
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
                vector<Person> person(cnt);
                   
                //Sort the personSpped in descending Order
                sort(objectYaml.personSpeed.begin(),objectYaml.personSpeed.begin()+cnt,greater<float>());

                //Calculate time of each person
                for(j=0;j<cnt;j++)
                {
                    person[j].walking_time = objectYaml.bridgesLength[i]/objectYaml.personSpeed[j];
                }
                
                totalTimeTaken = get_minimum_crossing_time(cnt,person) + totalTimeTaken;
        }
	return totalTimeTaken;

}

//return min bridge crossing time for n person(s)
//handle special cases if n = 0, n =1 , n =2, n = 3  
//handle special case if vector of person is not valis
unsigned int CrossingBridge::get_minimum_crossing_time(unsigned int n,vector<Person> person)
{
    if (n == 0)
    {
        return 0;
    }
    
    if (n < 3)
    {
        return person.back().walking_time;
    }
    else if (n == 3)
    {
        // Person 0 and 1 cross from A to B
        // Person 0 crosses back to A
        // Person 0 and 2 cross from A to B
        return person[1].walking_time + person[0].walking_time + person[2].walking_time; 
    }
    float time_taken = 0;

    // Person 0 and Person 1 cross from A to B
    time_taken += person[1].walking_time;

    // Person 1 crosses back to A
    time_taken += person[1].walking_time;

    // Person (n-2) and Person (n-1) cross from A to B
    time_taken += person[n-1].walking_time;

    // Person 0 goes back and forth to escort everyone else
    for (unsigned int i = 1; i < n-2; ++i)
    {
        // Person 0 crosses back to A
        time_taken += person[0].walking_time;

        // Person 0 and Person i cross from A to B
        time_taken += person[i].walking_time;
    }

    return time_taken;
}


int main(void)
{
	int status;
	
        //Create object to get the time taken to cross the bridge
	CrossingBridge getTime;
	float totalTimeTaken = getTime.getMinimumTime();
	printf("The Minimum crossing time: %f\n",totalTimeTaken);
	return 0;
	
}
