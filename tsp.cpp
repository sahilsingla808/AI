#include <iostream>
#include <cstdlib>

using namespace std;


double dis_bw_nodes(double d1, double d2);


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

	for (int i = 0; i < noofcities; ++i)
	{
		cout<<coordinates[i][0]<<"\t"<<coordinates[i][1]<<endl;
	}

	cout<<"\n\n\n\n\nDistance\n\n\n\n\n";

	for (i = 0; i < noofcities; ++i)
	{
		for (j = 0; j < noofcities; ++j)
		{
			cout<<node_distance[i][j]<<"\t";
		}
		cout<<endl;
	}




	return 0;
}


double dis_bw_nodes(double d1, double d2)
{
	if (d1>d2)
		return (d1-d2);
	else 
		return d2-d1;
	
}