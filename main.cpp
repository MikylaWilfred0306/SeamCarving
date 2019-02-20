#include <iostream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <fstream>
#include <string>
//g++ main.cpp -o a
using namespace std;

int energy(int x, int y, vector<vector <string> > vec){
    int total = 0;

    if ((x-1) >= 4 && vec[x-1].size() > y){
     total += std::abs(atoi(vec[x-1][y].c_str()) - atoi(vec[x][y].c_str()));
    }
   if ((y-1) >= 0 ){
     total += std::abs(atoi(vec[x][y-1].c_str())- atoi(vec[x][y].c_str()));
    }
    if ((x+1) < vec.size() && vec[x+1].size() > y){
     total += std::abs(atoi(vec[x+1][y].c_str()) - atoi(vec[x][y].c_str()));
    }
    if ((y+1) < vec[x].size()){
     total += std::abs(atoi(vec[x][y+1].c_str())- atoi(vec[x][y].c_str()));
    }

    return  std::abs (total);
}


int hor_energy(int x, int y, vector<vector <string> > vec){
    int total = 0;
 if(vec[x][y] != "F"){
    if ((x-1) >= 4 && vec[x-1].size() > y){
     if(vec[x-1][y] != "F") total += std::abs(atoi(vec[x-1][y].c_str()) - atoi(vec[x][y].c_str()));
    }
   if ((y-1) >= 0 ){
     if(vec[x][y-1] != "F") total += std::abs(atoi(vec[x][y-1].c_str())- atoi(vec[x][y].c_str()));
    }
    if ((x+1) < vec.size() && vec[x+1].size() > y){
     if(vec[x+1][y] != "F") total += std::abs(atoi(vec[x+1][y].c_str()) - atoi(vec[x][y].c_str()));
    }
    if ((y+1) < vec[x].size()){
     if(vec[x][y+1] != "F") total += std::abs(atoi(vec[x][y+1].c_str())- atoi(vec[x][y].c_str()));
    }
      return  std::abs (total);
 } else { return total = INT_MAX;}

}

vector<string> split(string str, string token){
    vector<string>result;
    while(str.size()){
        int index = str.find(token);
        if(index!=string::npos){
            result.push_back(str.substr(0,index));
            str = str.substr(index+token.size());
            if(str.size()==0)result.push_back(str);
        }else{
            result.push_back(str);
            str = "";
        }
    }
   return result;
}


void print2dvec(vector<vector <string> > vec){
for (int i = 0; i < vec.size(); i++)
{
    for (int j = 0; j < vec[i].size(); j++)
    {
        cout << vec[i][j] << " ";
    }

    cout << endl;
}

}

void print2dvec(vector<vector <int> > vec){
for (int i = 0; i < vec.size(); i++)
{
    for (int j = 0; j < vec[i].size(); j++)
    {
        cout << vec[i][j] << " ";
    }

    cout << endl;
}

}

void ver_seam_removal(int seams, std::vector<std::vector<string> > &vec) {
    for (int i=0; i<seams; ++i) {
            //cout << i << endl;

    std::vector<std::vector<int> > vec_energy;
    std::vector<std::vector<int> > cumla_vec;
    std::vector<std::vector<string> > final_vec;
    int left      =  INT_MAX;
     int right      =  INT_MAX;
    int track      =  0;
    int final_track      =  0;
    vector<int> result;
    vector<int> cumla_result;

 for (int i = 0; i < vec.size(); i++)
    {
        result.clear();
        cumla_result.clear();
        for (int j = 0; j < vec[i].size(); j++)
        {
            int energy_int = energy(i,j,vec);
            result.push_back(energy_int);

            if(i > 0){
                    if (j > 0)  {  left = energy_int + result[j-1]; }
                    if (j < vec[i].size()-1)  { right = energy_int + result[j+1]; }
                   track = energy_int + result[j];

                   if (right < left && right < track) final_track = right;
                   else if (left < right && left < track) final_track = left;
                   else final_track = track;
                   cumla_result.push_back(final_track);

            } else cumla_result.push_back(energy_int);

        }

        vec_energy.push_back(result);
        cumla_vec.push_back(cumla_result);

    }

       int minimum_index = 0;
  for (int i = 1; i < vec[vec.size()-1].size(); ++i) {;
      if (cumla_vec[vec.size()-1][minimum_index] > cumla_vec[vec.size()-1][i]) minimum_index = i;
  }

  for (int i = cumla_vec.size() - 1; i >= 0; --i) {

   int left_max     =  INT_MAX;
   int right_max     =  INT_MAX;
  int maxint     =  0;

   if (i > 4) {
     if (minimum_index != 0)  {  left_max = cumla_vec[i-1][minimum_index-1]; }
     if (minimum_index < vec.size() - 1)  { right_max = cumla_vec[i-1][minimum_index+1]; }
     maxint = cumla_vec[i-1][minimum_index];


     if (left_max <= right_max && left_max <= maxint) { vec[i-1][minimum_index-1]  = "-1"; --minimum_index; }
     else if(maxint <= left_max && right_max >= maxint) { if (vec[i-1].size()-1 > minimum_index) {vec[i-1][minimum_index]    = "-1"; }                 }
    else{ if((vec[i-1].size()-1) > (minimum_index+1)){vec[i-1][minimum_index+1]  = "-1";
        //minimum_index++;
       }}
   }
 }


  vector<string> final_vec_result;
char buffer [33];
for (int i = 0; i < vec.size(); i++)
{
     final_vec_result.clear();

    for (int j = 0; j < vec[i].size(); j++)
    {
        if (i == 2 and j == 0) {

               int size_square =  atoi(vec[i][j].c_str()) -1;
            final_vec_result.push_back(itoa(size_square,buffer,10)) ;}
        else if(vec[i][j] != "-1") {final_vec_result.push_back(vec[i][j]) ;}
    }

     final_vec.push_back(final_vec_result);
}


    vec.clear();
    vec = final_vec;
//print2dvec(vec);
  }
}


void attach_head ( std::vector<std::vector<string> > &vec, std::vector<std::vector<string> > &head, int carves){
vec[0] = head[0];
vec[1] = head[1];
vec[2] = head[2];
vec[3] = head[3];
char buffer [33];
 int size_square =  atoi(vec[2][1].c_str()) - carves;
vec[2][1]=itoa(size_square,buffer,10);

}

int largest_horzontal(std::vector<std::vector<string> > &vec){
    int size_int = 0;
for (int i = 4; i < vec.size(); i++)
{
    if(vec[i].size() > size_int) size_int = vec[i].size();
}
return size_int;

}

void rotate_hor(std::vector<std::vector<string> > &vec, std::vector<std::vector<string> > &header){
 for(int i=0; i<4; i++) {
    header.push_back(vec[i]);
}
  std::vector<std::vector<string> > rotated  (largest_horzontal(vec),  std::vector<string> (vec.size(), "F"));
  int x = largest_horzontal(vec);
  int y = vec.size();
  for(int i=4; i<y; i++) {
   for(int j=0; j<x; j++) {
      if (vec[i].size() > j)rotated[j][i]=vec[i][j];
   }
  }
  vec.clear();
  vec = rotated;

}

void rotate_ver(std::vector<std::vector<string> > &vec){
  std::vector<std::vector<string> > rotated;
  std::vector<string> rotated_result;
  int x = vec[0].size();
  int y = vec.size();
  for(int i=0; i<x; i++) {
    rotated_result.clear();
   for(int j=0; j<y; j++) {
      if (vec[j].size() > i) if (vec[j][i] != "F")  rotated_result.push_back(vec[j][i]);
   }
    rotated.push_back(rotated_result);
  }
  vec.clear();
  vec = rotated;

}

void hor_seam_removal(int seams, std::vector<std::vector<string> > &vec) {
    for (int i=0; i<seams; ++i) {

    std::vector<std::vector<int> > vec_energy;
    std::vector<std::vector<int> > cumla_vec;
    std::vector<std::vector<string> > final_vec;
    int left      =  INT_MAX;
     int right      =  INT_MAX;
    int track      =  0;
    int final_track      =  0;
    vector<int> result;
    vector<int> cumla_result;



    for (int i = 0; i < vec.size(); i++)
    {
        result.clear();
        cumla_result.clear();
        for (int j = 0; j < vec[i].size(); j++)
        {


           int energy_int = hor_energy(i,j,vec);
        result.push_back(energy_int);

            if(i > 0){
                    if (j > 0)  {  left = energy_int + result[j-1]; }
                    if (j < vec[i].size()-1)  { right = energy_int + result[j+1]; }
                   track = energy_int + result[j];

                   if (right < left && right < track) final_track = right;
                   else if (left < right && left < track) final_track = left;
                   else final_track = track;
                   cumla_result.push_back(final_track);

            } else cumla_result.push_back(energy_int);

        }

        vec_energy.push_back(result);
        cumla_vec.push_back(cumla_result);

    }

    int minimum_index = 0;
  for (int i = 1; i < vec[vec.size()-1].size(); ++i) {;
      if (cumla_vec[vec.size()-1][minimum_index] > cumla_vec[vec.size()-1][i]) minimum_index = i;
  }
  for (int i = cumla_vec.size() - 1; i >= 0; --i) {

   int left_max     =  INT_MAX;
   int right_max     =  INT_MAX;
  int maxint     =  0;

   if (i > 0) {
     if (minimum_index != 0)  {  left_max = cumla_vec[i-1][minimum_index-1]; }
     if (cumla_vec[i-1].size() - 1 > minimum_index+1)   if (minimum_index != vec.size() - 1)  { right_max = cumla_vec[i-1][minimum_index+1]; }
     if (cumla_vec[i-1].size() < minimum_index)  maxint = cumla_vec[i-1][minimum_index];

     if      (left_max < right_max && left_max < maxint) { vec[i-1][minimum_index-1]  = "-1"; --minimum_index; }
     else if ( maxint < left_max && right_max > maxint) { vec[i-1][minimum_index]    = "-1";                  }
     else{ vec[i-1][minimum_index+1]  = "-1"; ++minimum_index; }
   }
 }

  vector<string> final_vec_result;

for (int i = 0; i < vec.size(); i++)
{
     final_vec_result.clear();

    for (int j = 0; j < vec[i].size(); j++)
    {
        if(vec[i][j] != "-1") {final_vec_result.push_back(vec[i][j]) ;}
    }

     final_vec.push_back(final_vec_result);
}

    vec.clear();
    vec = final_vec;

  }
}




int main(int argc, char *argv[]){
	//First Parameter is the file
   char buffer [33];
    char* files;
    if (argc > 1) files = argv[1];
    else files = "test.pgm";

	//Second parameter is the vertical size
    char* vertical_carve;
    if (argc > 2) vertical_carve = argv[2];
    else vertical_carve = "20";

	//Third parameter is the horizontal size
    char* hor_carve;
    if (argc > 3) hor_carve = argv[3];
    else hor_carve = "15";

    std::string line;
    vector<vector <string> > vec;
    vector<vector <string> > head;
   ifstream qfile(files);

    if(!qfile)
    {
        cout<<"Error opening output file"<<endl;
        system("pause");
        return -1;
    }
    while (std::getline(qfile, line))
    {

        size_t found = line.find("\t");
        string delimeter = " ";
        if (found!=string::npos) delimeter = "\t";
        std::vector<string> vstrings = split(line, delimeter);

        vec.push_back(vstrings);
    }

    ver_seam_removal(atoi(vertical_carve),vec);
    rotate_hor(vec, head);
    hor_seam_removal(atoi(hor_carve),vec);
    rotate_ver(vec);
    attach_head(vec, head, atoi(hor_carve));
    //print2dvec(vec);


 std::ofstream myfile;
    std::string str(files);

    size_t lastindex = str.find_last_of(".");
    string rawname = str.substr(0, lastindex);

    rawname += "_processed.pgm";
   myfile.open(rawname.c_str(),  std::ios::binary);

   for (int i = 0; i < vec.size(); i++)
{
    for (int j = 0; j < vec[i].size(); j++)
    {
        myfile<<vec[i][j] << " ";
    }

    myfile << endl;
}
       myfile.close();
    return 0;
}
