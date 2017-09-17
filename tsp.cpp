#include <bits/stdc++.h>

using namespace std;

double cooling_factor = 0.999 , start_temp= 1e+10, end_temp=0.1 ;

double costfunc( vector<int> path_traverse , double **node_distance, double costprev);

double annealing(vector<int> path_traverse , double **node_distance, double total_dis);

int main(int argc, char const *argv[])
{
	cout.precision(12);

	string name;

	cin>>name;

	int noofcities,i,j;

	cin>>noofcities;

	double **coordinates = new double*[noofcities];

	for ( i = 0; i < noofcities; ++i)
	{
	  	coordinates[i]=new double[2];
	}  

	double x,y;

	for (i = 0; i < noofcities; ++i)
	{
		cin>>x>>y;
		coordinates[i][0]=x;
		coordinates[i][1]=y;
	}

	double **node_distance = new double*[noofcities];

	for ( i = 0; i < noofcities; ++i)
	{
	  	node_distance[i]=new double[noofcities];
	}

	for (i = 0; i < noofcities; ++i)
	{
		for (j = 0; j < noofcities; ++j)
		{
			cin>>x;
			node_distance[i][j]=x;
		}
	}


	vector<int> path_traverse(noofcities); 

	for (i = 0; i < noofcities; ++i)
	{
		path_traverse[i] = i;
	}

	random_shuffle( path_traverse.begin(), path_traverse.end() );

	double total_dis=0 , mindis=0;

	int x1,y1;

	for (int i = 0; i < noofcities-1 ; ++i)
	{
		x1=path_traverse[i];
		y1=path_traverse[i+1];
		total_dis+=node_distance[x1][y1];
	}

	cout<<total_dis;

	mindis = annealing(path_traverse,node_distance,total_dis);

	cout<<"\n\n\nPath it will Follow\n";
	for (int i = 0; i < noofcities; ++i)
	{
		cout<<path_traverse[i]<<"\t";
	}
	
	cout<<"\n\n\n\nDistace Travelled\n";
	cout<<mindis<<endl;

	return 0;
}


double annealing(vector<int> path_traverse , double **node_distance, double total_dis)
{
	double costprev = total_dis;
	double costbest = total_dis;
	double temp=start_temp, costnew,diff;

	vector<int> v = path_traverse;
	vector<int> vbes = path_traverse;

	while ( temp > end_temp )
	{
		costnew = costfunc(path_traverse , node_distance ,costprev);
		diff=costnew - costprev;
		if ( diff < 0 || exp(-diff/temp) > ((rand()%10000)/100000.0 ))
		{
			costprev=costnew;	
		}

		if (costbest > costnew )
		{
			costbest = costnew;
			vbes = path_traverse;
		}

		cout <<"costerfds "<< costprev<<endl;

		temp*=cooling_factor;
	} 



	path_traverse = vbes;
	return costbest;

}

double costfunc( vector<int> path_traverse , double **node_distance, double costprev)
{
	int x,y,cities=(path_traverse).size();

	double costnew;

	x=rand()%cities;
	y=rand()%cities;
	while(x==y)
	{
		y=rand()%cities;
	}

	costnew = costprev - node_distance[path_traverse[x-1]][path_traverse[x]] - node_distance[path_traverse[x]][path_traverse[x+1]] - node_distance[path_traverse[y-1]][path_traverse[y]] - node_distance[path_traverse[y]][path_traverse[y+1]];

	cout <<"prev cost \t"<<costnew<<endl;

	int temp;

	temp =  path_traverse[x];
	path_traverse[x]=path_traverse[y];
	path_traverse[y]=temp;

	costnew+=node_distance[path_traverse[x-1]][path_traverse[x]] + node_distance[path_traverse[x]][path_traverse[x+1]] + node_distance[path_traverse[y-1]][path_traverse[y]] + node_distance[path_traverse[y]][path_traverse[y+1]];
	
	cout <<"after cost \t"<<costnew<<endl;

	return costnew;
}