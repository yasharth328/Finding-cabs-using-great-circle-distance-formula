//CPP code to find cabs nearby


#include<bits/stdc++.h>
using namespace std;


//Latitude of customer who needs a cab
#define lat1d 12.961159
 
// Logitude of customer who need a cab
#define lon1d 77.6362214

#define pi 3.14159265358979323846
#define earth_radius 6317.0

ifstream customer_list ("customer.json");
ofstream out ("answer.json");


//Function to convert degree to radian.

double degtorad(double deg)
{
    return (deg*pi/180);
}

// Function to calculate distance
//between 2 given locations
//using Great Cirlce distance formula
double distanceFromEarth(double lat2d,double lon2d)
{

    double latitude1,longitude1,latitude2,longitude2,delta_lon, central_ang;

            latitude1 = degtorad(lat1d);
            latitude2 = degtorad(lat2d);
            longitude1 = degtorad(lon1d);
            longitude2 = degtorad(lon2d);

            delta_lon = longitude2 - longitude1;

            //great cicrle distance formula
            central_ang = acos(sin(latitude1)*sin(latitude2)+ cos(latitude1)*cos(latitude2)*cos(delta_lon));
            
            return (earth_radius*central_ang);
            
}

//Structure which contains data and 
// functions for accesing and processing
//data from the given customers.json file.

struct json
{

/*
    i and j are used to access various 
    elements of the char array. x is used to measure
    the size of the element of latitude_as_string array.
    y is used to measure the size of the element of id_as_string
    array. m is used to measure the size of the element of
    name array. f keeps count of " " " symbol. fi keeps count of
    ": " symbol.
*/
     long long int length,i,j,x,y,m,
                    n,f,fi,id[100000];


     char latitude_as_string[1000],
          longitude_as_string[1000],
          id_as_string[1000], name[1000];


        double lat2d,lon2d;

    //To ger each line of customers.json
    //file as string.
    string line;

    //functionto check weather distance between
    // 2 points is less than 50km or not.
    void distance_calculator()
    {
        {
            if(distanceFromEarth(lat2d, lon2d)<= 50.0000)
            {
                // Converting if to int format.
                id[i] = atoll(id_as_string);
                i++;
                cout<< "{\"user_id:  "<< id[i-1] <<",\"name\": "<< name << "}" <<endl;

            }

        }
    }


        //Function to read various attributes
        // like latitude, longitude, name,id,
        //etc, from customer.json file. simplistic 
        //approach is used to get JSON attributes.
        void json_parser()
        {
            if (customer_list.is_open())
            {

                while(getline(customer_list,line))
                {
                    f = 0;x=0;y=0;fi=0;m=0;n=0;
                    length = line.size();


                    for(j=0;j<length;j++)
                    {
                        
                        if(line[j]=='"')
                        f++;

                        else if(line[j]==':')
                        fi++;

                        // To get latitude of the location.
                        if(f==3)
                        {

                            j++;

                            while(line[j]!='"')
                            latitude_as_string[x] = line[j];
                            x++;j++;
                        }
                        // To get longitude of the location.
                        else if(f==13)
                        {

                                j++;
                                while(line[j]!='"')
                               {
                                    longitude_as_string[y] = line[j];
                                    y++;j++;
                               }
                            
                            j--; longitude_as_string[y] = '\0';

                        
                        }

                    // To get id of friend.
                    if(fi==2)
                    {
                         j += 2;
  
                        while (line[j] != ',')
                        {
                            id_as_string[m] = line[j];
                            m++; j++;
                        }
  
                        j--; id_as_string[m] = '\0';
                        fi++;
                    }

                        //To get name to the friend.
                        else if(fi==4)
                        {
                            j+=2;

                            while(line[j] != ',')
                            {
                                name[n] = line[j];
                                n++;j++;
                            }

                            j--; name[n] = '\0';
                            fi++; f+=2;

                       }

                    }
                    // Converting latitude and longitude
                    // in string to float.
                    lat2d = atof(latitude_as_string);
                    lon2d = atof(longitude_as_string);
                    distance_calculator();

                }

            }

            // closing stream of customer's file.
            customer_list.close();
          
            // closing stream of answer's file.
            out.close();

        }
};

int main()
{
    // creating objects of the structure json
    json obj;

    //To read customer.json file.
    obj.json_parser();
    return 0;

}

