#include <bits/stdc++.h>

using namespace std;

long double cooling_factor = 0.9999 , start_temp= 1e+30, end_temp=0.1 ;

long double costfunc( vector<int> &vbes , long double **node_distance, long double costprev);

long double annealing(vector<int> &path_traverse , long double **node_distance, long double total_dis);

int main(int argc, char const *argv[])
{
	cout.precision(12);

	string name;

	cin>>name;

	int noofcities,i,j;

	cin>>noofcities;

	long double **coordinates = new long double*[noofcities];

	for ( i = 0; i < noofcities; ++i)
	{
	  	coordinates[i]=new long double[2];
	}  

	long double x,y;

	for (i = 0; i < noofcities; ++i)
	{
		cin>>x>>y;
		coordinates[i][0]=x;
		coordinates[i][1]=y;
	}

	long double **node_distance = new long double*[noofcities];

	for ( i = 0; i < noofcities; ++i)
	{
	  	node_distance[i]=new long double[noofcities];
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
	vector<int> path_traverse2(noofcities); 

	for (i = 0; i < noofcities; ++i)
	{
		path_traverse[i] = i;
	}

	cout<<"\n\n\nPath it will Follow\n";
	for (int i = 0; i < noofcities; ++i)
	{
		cout<<path_traverse[i]<<"\t";
	}

	srand (time(NULL));
	random_shuffle( path_traverse.begin(), path_traverse.end() );

	cout<<"\n\n\nPath it will Follow\n";
	for (int i = 0; i < noofcities; ++i)
	{
		cout<<path_traverse[i]<<"\t";
	}

	long double total_dis=0 , mindis=0;

	int x1,y1;

	for (int i = 0; i < noofcities-1 ; ++i)
	{
		x1=path_traverse[i];
		y1=path_traverse[i+1];
		total_dis+=node_distance[x1][y1];
	}

	cout<<"initial :: "<<total_dis;

	// int x2,y2,cities=(path_traverse).size();

	// long double costnew=0, costans=0;

	// x2=rand()%cities;
	// srand (time(NULL));
	// y2=rand()%cities;
	// srand (1);
	// while(x2==y2)
	// {
	// 	y2=rand()%cities;
	// }

	// cout<<"\ncoordinates :: "<<x2<<"\t"<<y2<<endl;

	// cout<<node_distance[path_traverse[x2-1]][path_traverse[x2]]<<"\t"<< node_distance[path_traverse[x2]][path_traverse[x2+1]]<<"\t"<<node_distance[path_traverse[y2-1]][path_traverse[y2]]<<"\t"<<node_distance[path_traverse[y2]][path_traverse[y2+1]];


	// costnew = total_dis - node_distance[path_traverse[x2-1]][path_traverse[x2]] - node_distance[path_traverse[x2]][path_traverse[x2+1]] - node_distance[path_traverse[y2-1]][path_traverse[y2]] - node_distance[path_traverse[y2]][path_traverse[y2+1]];

	// cout <<"prev cost \t"<<costnew<<endl;

	// int temp;

	// temp =  path_traverse[x2];
	// path_traverse[x2]=path_traverse[y2];
	// path_traverse[y2]=temp;

	// cout<<"\n\n\nPath it will Follow\n";
	// for (int i = 0; i < noofcities; ++i)
	// {
	// 	cout<<path_traverse[i]<<"\t";
	// }
	// cout<<endl;

	// cout<<path_traverse[x2-1]<<"\t"<<path_traverse[x2]<<endl;

	// costans = costnew + node_distance[path_traverse[x2-1]][path_traverse[x2]] + node_distance[path_traverse[x2]][path_traverse[x2+1]] + node_distance[path_traverse[y2-1]][path_traverse[y2]] + node_distance[path_traverse[y2]][path_traverse[y2+1]];
	
	// cout<<endl<<node_distance[path_traverse[x2-1]][path_traverse[x2]]<<"\t"<< node_distance[path_traverse[x2]][path_traverse[x2+1]]<<"\t"<<node_distance[path_traverse[y2-1]][path_traverse[y2]]<<"\t"<<node_distance[path_traverse[y2]][path_traverse[y2+1]];

	// cout <<"\nafter cost \t"<<costans<<endl;

	mindis=total_dis;
	for (int i = 0; i < 10000 ; ++i)
	{
		mindis = annealing(path_traverse,node_distance,mindis);

		
		if (total_dis > mindis && mindis >0)
		{
			total_dis=mindis;
			path_traverse2=path_traverse;
		}
		cout<<"\n\n\nPath it will Follow\n";
		for (int i = 0; i < noofcities; ++i)
		{
			cout<<path_traverse2[i]<<"\t";
		}
		cout<<"\n\n\n\nDistace Travelled\n";
		cout<<total_dis<<endl;
	}
	


	cout<<"\n\n\nPath it will Follow\n";
	for (int i = 0; i < noofcities; ++i)
	{
		cout<<path_traverse[i]<<"\t";
	}
	total_dis=0;
	for (int i = 0; i < noofcities-1 ; ++i)
	{
		x1=path_traverse[i];
		y1=path_traverse[i+1];
		total_dis+=node_distance[x1][y1];
	}

	cout<<"\nCalculated\n"<<total_dis;
	
	cout<<"\n\n\n\nDistace Travelled\n";
	cout<<mindis<<endl;

	return 0;
}


long double annealing(vector<int> &path_traverse , long double **node_distance, long double total_dis)
{
	long double costprev = total_dis;
	long double costbest = total_dis;
	long double temp=start_temp, costnew,diff;
	int cities=cities=(path_traverse).size();
	vector<int> v(path_traverse);
	vector<int> vbes(path_traverse);

	while ( temp > end_temp )
	{
		costnew = costfunc(vbes , node_distance ,costprev);
		diff=costnew - costprev;
		if ( (diff < 0) || ((exp(-diff/temp)) > ((rand()%10000)/10000.0 )))
		{
			costprev=costnew;	
		}

		if (costbest > costprev )
		{
			costbest = costprev;
			for (int i = 0; i < cities; ++i)
			{
				path_traverse[i]=vbes[i];
			}
			
		}

		//cout <<"costerfds "<< costprev<<endl;

		temp*=cooling_factor;
	}

	// cout<<"\nvbes";
	// cout<<endl<<endl;
	// for (int i = 0; i < cities; ++i)
	// {
	// 	cout<<path_traverse[i]<<"\t";
	// }
	// cout<<endl;
	return costbest;

}

long double costfunc( vector<int> &vbes , long double **node_distance, long double costprev)
{
	int x,y,cities=(vbes).size();

	long double costnew=0, costans=0;

	srand (time(NULL));
	x=rand()%cities;
	srand (1);
	y=rand()%cities;
	while(x==y)
	{
		y=rand()%cities;
		srand (1);
	}

	// costnew = costprev - node_distance[vbes[x-1]][vbes[x]] - node_distance[vbes[x]][vbes[x+1]] - node_distance[vbes[y-1]][vbes[y]] - node_distance[vbes[y]][vbes[y+1]];

	//cout <<"prev cost \t"<<costnew<<endl;

	int temp;

	reverse(vbes.begin()+x,vbes.begin()+y);

	// temp =  vbes[x];
	// vbes[x]=vbes[y];
	// vbes[y]=temp;

	// costans = costnew + node_distance[vbes[x-1]][vbes[x]] + node_distance[vbes[x]][vbes[x+1]] + node_distance[vbes[y-1]][vbes[y]] + node_distance[vbes[y]][vbes[y+1]];
	
	costans=0;
	int x1,y1;
	for (int i = 0; i < cities-1 ; ++i)
	{
		x1=vbes[i];
		y1=vbes[i+1];
		costans+=node_distance[x1][y1];
	}

	// costans=0;
	
	// for (int i = 0; i < cities-1 ; ++i)
	// {
	// 	x1=vbes[i];
	// 	y1=vbes[i+1];
	// 	costans+=node_distance[x1][y1];
	// }
	
	// srand (time(NULL));
	// random_shuffle( vbes.begin(), vbes.end() );
	// int x1,y1;

	



	//cout <<"after cost \t"<<costans<<endl;

	return costans;
}