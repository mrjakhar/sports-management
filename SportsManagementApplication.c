#include<stdio.h>
#include<string.h>
#include<stdlib.h>

enum status {FAILURE, SUCCESS};
#define n 5
struct Ground_db
{
	char ground_name[20];
	char city[15];
	char state[15];
	
	struct games
	{
		char game_name[15];
		int hourly_rate;
		
		struct dates
		{
			int date;
			int times[5];
			int timee[5];		
		}dates[5];		
		
		
	}game[5];
	
}ground_db[5];

struct data
{
	char ground_nm[20];
	char game_nm[15];
	int dateOf;
	int time;
} data_sort[100];

void init(int start){
	int i,j,k;
	for(i=start; i<5; i++)
	{
		ground_db[i].ground_name[0] = '\0';
		ground_db[i].city[0] = '\0';
		ground_db[i].state[0] = '\0';
		for(j=0; j<5; j++){
			ground_db[i].game[j].hourly_rate = 0;
			ground_db[i].game[j].game_name[0] = '\0';
			for(k=0; k<5; k++){
				ground_db[i].game[j].dates[k].date = 0;
				ground_db[i].game[j].dates[k].times[k] = 0;
				ground_db[i].game[j].dates[k].timee[k] = 0;
			}
		}
	}
}
int datec[5][5];								//datec a 2-D array storing the count of no. of dates for each game of each ground
int timingc[5][5][5];							//timingc a 3-D array storing the count of no. of time slot for each date of each game of each ground

int sortSport(int i, int co[]){
	int got=0, p, q;
	if(co[i+1]>1){
		struct games temp_game;
		for(p=1; p<co[i+1] ; p++){
			temp_game = ground_db[i+1].game[p] ;
			q = p ;
			while(strcmp(ground_db[i+1].game[q-1].game_name, temp_game.game_name)>0){
				ground_db[i+1].game[q] = ground_db[i+1].game[q-1];
				q--;
			}
			ground_db[i+1].game[q] = temp_game;
		}
	}
}


int sortGround(int size, int co[]){
	int i, j, swap=1, got=0, p, q;
	struct Ground_db temp;
	for(i=0; i<=size && swap==1; i++){
		swap = 0;
		for(j=1; j<=size-i; j++){
			if(strcmp(ground_db[j-1].ground_name, ground_db[j].ground_name)>0){
				temp = ground_db[j-1];
				ground_db[j-1] = ground_db[j];
				ground_db[j] = temp;
				swap = 1 ;
			}
			else if(strcmp(ground_db[j-1].ground_name, ground_db[j].ground_name)==0)
			{
				if(strcmp(ground_db[j-1].city, ground_db[j].city)>0)
				{
					temp = ground_db[j-1];
					ground_db[j-1] = ground_db[j];
					ground_db[j] = temp;
					swap = 1 ;
				}
			}
		}
	}
}

int addData(int nod, int co[]){
	int c=0;
	for(int i=0;i<=nod; i++){
		for(int j=0; j<co[i]; j++){
			for(int k=0; k<datec[i][j]; k++){
				for(int l=0; l<timingc[i][j][k]; l++){
					strcpy(data_sort[c].ground_nm, ground_db[i].ground_name);
					strcpy(data_sort[c].game_nm, ground_db[i].game[j].game_name);
					data_sort[c].dateOf = ground_db[i].game[j].dates[k].date;
					data_sort[c].time = ground_db[i].game[j].dates[k].times[l];
					c++;
				}
			}
		}
	}
	return c;
}

int getFixturesortedOnDate(int nod, int co[]){
	int len, sorted=0;
	struct data temp;
	len = addData(nod, co);
	for(int i=0; i<len; i++){
		for(int j=1; j<len-i-1; j++){
			if(data_sort[j-1].dateOf > data_sort[j].dateOf){
				temp = data_sort[j-1];
				data_sort[j-1] = data_sort[j];
				data_sort[j] = temp;
			}

			else if(data_sort[j-1].dateOf == data_sort[j].dateOf){
				if(data_sort[j-1].time > data_sort[j].time){
					temp = data_sort[j-1];
					data_sort[j-1] = data_sort[j];
					data_sort[j] = temp;
				}
			}
		}
	}

	for(int i=0; i<len; i++){
		printf("\nDate : %d\n", data_sort[i].dateOf);
		printf("\tTime : %d\n", data_sort[i].time);
		printf("\t\tGround : %s\n", data_sort[i].ground_nm);
		printf("\t\tCity : %s\n", data_sort[i].game_nm);
	}

}



int checkDuplicate(struct Ground_db temp_check, int stop){
	int index;
	for(index=0; index<stop; index++){
		if(strcmp(ground_db[index].ground_name, temp_check.ground_name)==0 && strcmp(ground_db[index].city, temp_check.city)==0)
		{ 
			return FAILURE;
		}	
	}
	return SUCCESS;
}

int addGround(int i, int co[]){
	int j,k,tss,tse;
	struct Ground_db temp;
	printf("\nGround Name : ");
	scanf("%s",temp.ground_name);
	printf("\nCity : ");
	scanf("%s",temp.city);
	printf("\nState : ");
	scanf("%s",temp.state);
	printf("\nName of sport : ");
	scanf("%s",temp.game[co[i]].game_name);						
	printf("\nHow many dates are scheduled  ");
	int nod;
	scanf("%d",&nod);
	for(j=0;j<nod;j++){
		printf("\nDate : ");
		scanf("%d",&temp.game[co[i]].dates[j].date);
		printf("\nHow many time slots are scheduled ? ");
		int nts;
		scanf("%d",&nts);					
		for(k=0;k<nts;k++)
		{
			printf("\n Enter start time and end time : \n");
			scanf("%d",&temp.game[co[i]].dates[j].times[k]);
			printf("\t");
			scanf("%d",&temp.game[co[i]].dates[j].timee[k]);			
		}
	}
	if(i>0){
		int status = checkDuplicate(temp, i);
		if(status == 1)
		{
			ground_db[i] = temp; 
			co[i]++;
			return SUCCESS;		
		}	
		else 
			return FAILURE;
	}
	else{
		ground_db[i] = temp;
		co[i]++;
		return SUCCESS;
	}
}



void display(int index,int gno[]){
	int i,j;
	for(i=0; i<=index; i++){
		printf("\n\t Ground No %d :-\n", i+1);
		printf("\nGround Name : %s\n", ground_db[i].ground_name);
		printf("\nCity : %s\n", ground_db[i].city);
		printf("\nState : %s\n", ground_db[i].state);
		printf("\nSports :\n");
		for(j=0;j<gno[i];j++)
			printf("%s\n",ground_db[i].game[j].game_name);
	
	}
	
}

int getGroundInfo(int nod, int count[]){
	char in_city[15];
	int c=0,i,j;
	printf("\nEnter city : ");
	scanf("%s", in_city);

	printf("\nGrounds in %s are : \n", in_city);
	for(i=0; i<=nod; i++){

		if(strcmp(ground_db[i].city, in_city)==0){
			printf("\nGround : %s\n", ground_db[i].ground_name);
			printf("\nSports : \n");
			for(j=0; j<count[i]; j++){
				printf("\t%s\n", ground_db[i].game[j].game_name);
			}
			c++;
		}
	}

	return c;
}

int deleteGround(int len){ 
	char dele_city[15], dele_ground[20];
	printf("\nWhich Ground in City needs to be deleted ? \n");
	scanf("%s", dele_ground);
	scanf("%s", dele_city);
	int i;
	for(i=0; i<len; i++){
		if(strcmp(dele_ground,ground_db[i].ground_name)==0 && strcmp(dele_city, ground_db[i].city)==0){
			int j = i;
			while(j<len-1){
				ground_db[j]=ground_db[j+1];
				j++;
			}
			init(len);
			return SUCCESS;
		}
	}
	return FAILURE;

}

int updateGround(int len, int co[]){
	char toUpdate_ground_name[20], toUpdate_city[15];
	int ret_val,i;
	printf("\nWhich Ground Record needs to be Updated ?\n");
	scanf("%s", toUpdate_ground_name);
	scanf("%s", toUpdate_city);
	for(i=0; i<len; i++){
		if(strcmp(toUpdate_ground_name,ground_db[i].ground_name)==0 && strcmp(toUpdate_city, ground_db[i].city)==0){
			addGround(i, co);
			return SUCCESS;
		}
	}
	return FAILURE;
}


void statesort(int num)
{
	int i,j,sorted=0;
	struct Ground_db temp;
	for(i=0;i<=num-1 && sorted==0;i++)
	{
		sorted=1;
		for(j=1;j<=num-i;j++)
		{
			int p=strcmp(ground_db[j-1].state,ground_db[j].state);
			if(p>=0)
			{
				if(p>0)
				{
					temp=ground_db[j-1];
					ground_db[j-1]=ground_db[j];
					ground_db[j]=temp;
					sorted=0;
				}
				if(p==0)
				{
					int citys=strcmp(ground_db[j-1].city,ground_db[j].city);
					if(citys>0)
					{
						temp=ground_db[j-1];
						ground_db[j-1]=ground_db[j];
						ground_db[j]=temp;
						sorted=0;
					}
				}
			}
		}
	}
	
}

int addSport(int c,int countsport[])					
{
	int i,j,flag=0,retval=-1,dateof,k,tss,tse;
		char groundname[50],cityname[20];
		printf("\n Enter ground name\n");
					scanf("%s",groundname);
					printf("\n Enter city name\n");
					scanf("%s",cityname);
	for(i=0;i<=c && flag==0;i++)
	{
		if(strcmp(ground_db[i].ground_name,groundname)==0 && strcmp(ground_db[i].city,cityname)==0)
		{
			
				printf("\n Enter name of sport");
				scanf("%s",ground_db[i].game[countsport[i]].game_name);
				printf("\nEnter hourly rate of this sport");
				scanf("%d",&ground_db[i].game[countsport[i]].hourly_rate);						
				printf("\n first enter number of dates you want to hold this sport ");
				int nod;											//nod denoting no. of dates
				scanf("%d",&nod);
				for(j=0;j<nod;j++)
					{
						datec[i][countsport[i]]=nod;
						printf("\n Enter date");
						scanf("%d",&dateof);
						ground_db[i].game[countsport[i]].dates[j].date=dateof;
						printf("\n enter the number of time slots");
						int nts;										//nts is no. of timeslots
						scanf("%d",&nts);
						
						for(k=0;k<nts;k++)
						{
							timingc[i][countsport[i]][j]=nts;
							printf("\n now enter starting and ending time of your time slot");
							scanf("%d",&tss);
							ground_db[i].game[countsport[i]].dates[j].times[k]=tss;
							scanf("%d",&tse);
							ground_db[i].game[countsport[i]].dates[j].timee[k]=tse;
							
						}
					}
				retval=i;
				flag=1;
	
		}
	}
	return retval;	
	
}

int deleteSport(int gno,int countsport[])						//co array is total no. of sports in a ground,gno is no. of grounds
{
	int i,j,k,retval=-1,flag=0;
	char dele_ground[20],dele_city[15],dele_sport[15];
	printf("\nenter ground and city of sport you want to delete\n");
	scanf("%s",dele_ground);
	scanf("%s",dele_city);
	printf("\n Enter name of sport");
	scanf("%s",dele_sport);
	for(i=0;i<=gno && flag==0;i++)
	{
		if(strcmp(ground_db[i].ground_name,dele_ground)==0 && strcmp(ground_db[i].city,dele_city)==0)
		{		
				for(j=0;j<countsport[i];j++)
				{
					if(strcmp(ground_db[i].game[j].game_name,dele_sport)==0)
					{
						for(k=j;k<countsport[i];k++)
						  ground_db[i].game[k]=ground_db[i].game[k+1];
						countsport[i]--;
						retval=1;
						flag=1; 
					}
				}
	    }
	}
	return retval;
}


int FindlocationsforGameInTimeRange(int nod,int count[])
{
	int i,j,orgdate,startTime,endTime,k,c=0,found=0,l;			//orgdate is organising date
	char spname[15];
	while(found==0){
		printf("\nEnter the sport you want to check for : ");	
		scanf("%s",spname);
		for(i=0; i<=nod && found==0; i++){
			for(j=0; j<count[i] && found==0; j++){
				if(strcmp(ground_db[i].game[j].game_name, spname)==0){
					found=1;
				}
			}
		}
		if(found==0){
			printf("\nInvalid game name...\nEnter again --- \n");
		}
	}
	printf("\nEnter the date");
	scanf("%d",&orgdate);
	printf("\nEnter start time : ");
	scanf("%d", &startTime);
	printf("\n Enter End time : ");
	scanf("%d", &endTime);
if(startTime>=1000 && endTime<=2300)					//keeping a mandatory condition that ground can hold matches between 10:00-23:00
{

	for(i=0;i<=nod; i++)
	{
		for(j=0;j<count[i];j++)
		{
			if(strcmp(ground_db[i].game[j].game_name,spname)==0)
			{
					
				for(k=0;k<datec[i][j];k++)
				{
					if((ground_db[i].game[j].dates[k].date)==orgdate)
					{
						int flag=0;
						for(l=0;l<timingc[i][j][k] && flag==0;l++)
						{
							if(startTime<ground_db[i].game[j].dates[k].times[0] && endTime<ground_db[i].game[j].dates[k].times[0])
							{
									printf("\nGround : %s",ground_db[i].ground_name);
									printf("\nCity: %s",ground_db[i].city);
									printf("\n");
									c++;
									flag=1;
							}
						else{
							
							if(timingc[i][j][k]>1 && ground_db[i].game[j].dates[k].timee[l]<=startTime && ground_db[i].game[j].dates[k].times[l+1]>=endTime )
								{
									printf("\nGround : %s",ground_db[i].ground_name);
									printf("\nCity: %s",ground_db[i].city);
									printf("\n");
									c++;
									flag=1;
								}
							
							else{
									if(startTime>ground_db[i].game[j].dates[k].timee[timingc[i][j][k]-1]&& endTime>ground_db[i].game[j].dates[k].timee[timingc[i][j][k]-1])
									{	
										printf("\nGround : %s",ground_db[i].ground_name);
										printf("\nCity: %s",ground_db[i].city);
										printf("\n");

										c++;
										flag=1;
									}
								}
							}
						}
				    }
				}
			}
		}
	}
}
	return c;
} 

int getFixturesinCity(int nod, int co[]){
	int found=0, i, j, k, lo_date, hi_date, c=0;
	char get_city[15];
	while(found==0){
		printf("\nEnter the city you want to check for : ");	
		scanf("%s", get_city);
		for(i=0; i<=nod && found==0; i++){
			for(j=0; j<co[i] && found==0; j++){
				if(strcmp(ground_db[i].city, get_city)==0){
					found=1;
				}
			}
		}
		if(found==0){
			printf("\nInvalid game name...\nEnter again --- \n");
		}
	}
	printf("\nEnter range of dates : \n");
	scanf("%d", &lo_date);
	scanf("%d", &hi_date);

	for(i=0; i<=nod; i++){
		if(strcmp(ground_db[i].city, get_city)==0){
			printf("%s : \n", ground_db[i].ground_name);
			for(j=0; j<co[i]; j++){
				for(k=0; k<datec[i][j]; k++){
					if(ground_db[i].game[j].dates[k].date>=lo_date && ground_db[i].game[j].dates[k].date<=hi_date){
						printf("\t%s on %d\n", ground_db[i].game[j].game_name, ground_db[i].game[j].dates[k].date);
						c++;
					}
				}
			}
		}	
	}
	return c;		
}

int getFixturesinState(int nod, int co[]){
	int i, j, c=0, found=0, index[5]={0}, x=0;
	char get_state[15];											/*printf("\nEnter city name of that state");
																	scanf("%s",cname);for(i=0;i<=nod;i++)
																	{if(strcmp(ground_db[i].city,cname)==0)strcpy(ground_db[i].state,get_state)}*/
	while(found==0){
		printf("\nEnter the state you want to check for : ");	
		scanf("%s", get_state);
		for(i=0; i<=nod && found==0; i++){
			for(j=0; j<co[i] && found==0; j++){
				if(strcmp(ground_db[i].state, get_state)==0){
					found=1;
				}
			}
		}
		if(found==0){
			printf("\nInvalid game name...\nEnter again --- \n");
		}
	}
	for(i=0; i<=nod; i++){
		if(strcmp(ground_db[i].state, get_state)==0){
			index[x]=i;
			x++;
		}
	}

	int sorted=0;
	struct Ground_db temp;
	for(i=0; i<x && sorted==0; i++){
		sorted=1;
		for(j=1; j<x-i; j++){
			int citys = strcmp(ground_db[index[j-1]].city, ground_db[index[j]].city);
				if(citys>0){
					temp = ground_db[index[j-1]];
					ground_db[index[j-1]] = ground_db[index[j]];
					ground_db[index[j]] = temp ; 
					sorted = 0;
				}
		}
	}

	printf("\nSports in %s are : \n", get_state);
	for(i=0; i<x; i++){
		printf("\nGround : %s\n", ground_db[index[i]].ground_name);
		printf("\nCity : %s\n", ground_db[index[i]].city);
		for(j=0; j<co[index[i]]; j++){
			printf("%s\n", ground_db[index[i]].game[j].game_name);
		}
		printf("\n");
	}
	
	
}


int FindlocationsforGame(int nod,int count[])
{
	int i,j,orgdate,orgtime,k,c=0,found=0,l;			//orgdate is organising date
	char spname[15];
	while(found==0){
		printf("\nEnter the sport you want to check for : ");	
		scanf("%s",spname);
		for(i=0; i<=nod && found==0; i++){
			for(j=0; j<count[i] && found==0; j++){
				if(strcmp(ground_db[i].game[j].game_name, spname)==0){
					found=1;
				}
			}
		}
		if(found==0){
			printf("\nInvalid game name...\nEnter again --- \n");
		}
	}
	printf("\nEnter the date :");
	scanf("%d",&orgdate);
	printf("\nEnter time of game");
	scanf("%d",&orgtime);
	if(orgtime>=1000 && orgtime<=2300)       			//every ground can hold event only from 10:00 - 23:00
	{
	
	for(i=0;i<=nod; i++)
	{
		int j;
		for(j=0;j<count[i];j++)
		{
			if(strcmp(ground_db[i].game[j].game_name, spname)==0)
			{
				for(k=0;k<datec[i][j];k++)
				{
					if((ground_db[i].game[j].dates[k].date)==orgdate)
					{
						int flag=0;
						for(l=0;l<timingc[i][j][k] && flag==0;l++)
						{
							if(orgtime<ground_db[i].game[j].dates[k].times[0])
							{
									printf("\nGround : %s",ground_db[i].ground_name);
									printf("\nCity: %s",ground_db[i].city);
									printf("\n");
									c++;
									flag=1;
							}
						else{
							
							if(timingc[i][j][k]>1 && ground_db[i].game[j].dates[k].timee[l]<=orgtime && ground_db[i].game[j].dates[k].times[l+1]>=orgtime )
								{
									printf("\nGround : %s",ground_db[i].ground_name);
									printf("\nCity: %s",ground_db[i].city);
									printf("\n");
									c++;
									flag=1;
								}
							
							else{
									if(orgtime>ground_db[i].game[j].dates[k].timee[timingc[i][j][k]-1])
									{	
										printf("\nGround : %s",ground_db[i].ground_name);
										printf("\nCity: %s",ground_db[i].city);
										printf("\n");
										c++;
										flag=1;
									}
								}
							}
						/*	if(ground_db[i].game[j].dates[k].times[l]<=orgtime && ground_db[i].game[j].dates[k].timee[l]>=orgtime)
							{
								printf("\nGround : %s",ground_db[i].ground_name);
								printf("\nCity: %s",ground_db[i].city);
								c++;
							}
						*/
						}
				    }
				}
			}
		}
	}		
	return c;
 }
}

int FindlocationsforGameEvent(int nod,int count[])
{
	int i,j,orgdate, startTime, found=0, endTime, k,c=0,l;			//orgdate is organising date
	char spname[15];
	while(found==0){
		printf("\nEnter the sport you want to check for : ");	
		scanf("%s",spname);
		for(i=0; i<=nod && found==0; i++){
			for(j=0; j<count[i] && found==0; j++){
				if(strcmp(ground_db[i].game[j].game_name, spname)==0){
					found=1;
				}
			}
		}
		if(found==0){
			printf("\nInvalid game name...\nEnter again --- \n");
		}
	}
	printf("\nEnter the date : ");
	scanf("%d",&orgdate);
	printf("\nEnter start time : ");
	scanf("%d", &startTime);
	printf("\n Enter End time : ");
	scanf("%d", &endTime);
	for(i=0;i<=nod;i++)
	{
		for(j=0;j<count[i];j++)
		{
			if(strcmp(ground_db[i].game[j].game_name,spname)==0)
			{
				for(k=0;k<datec[i][j];k++)
				{
					if((ground_db[i].game[j].dates[k].date)==orgdate)
					{
						for(l=0;l<timingc[i][j][k];l++)
						{
							if(ground_db[i].game[j].dates[k].times[l]<=startTime && ground_db[i].game[j].dates[k].timee[l]>=endTime)
							{
								printf("\nGround : %s",ground_db[i].ground_name);
								printf("\nCity: %s\n",ground_db[i].city);
								printf("\n");
								c++;
							}
						}
				    }
				}
			}
		}
	}		
	return c;
} 

int isAvailable(int num, int co[]){
	char game_srch[15], print_ground[20],i,j,k,l;
	int date_srch, time_srch, index[5] = {0}, x=0, found=0; 
	while(found==0){
		printf("\nEnter the sport you want to check for : ");	
		scanf("%s", game_srch);
		for(i=0; i<=num && found==0; i++){
			for(j=0; j<co[i] && found==0; j++){
				if(strcmp(ground_db[i].game[j].game_name, game_srch)==0){
					found=1;
				}
			}
		}
		if(found==0){
			printf("\nInvalid game name...\nEnter again --- \n");
		}
	}
	printf("\nEnter DAte and Time : ");
	scanf("%d",&date_srch);
	scanf("%d",&time_srch);
	for(i=0;i<=num;i++)
	{
		for(j=0;j<co[i];j++)
		{
			if(strcmp(ground_db[i].game[j].game_name, game_srch)==0)
			{
				for(i=0;i<=num;i++)
				{
					for(j=0;j<co[i];j++)
					{
						if(strcmp(ground_db[i].game[j].game_name, game_srch)==0)
						{
							for(k=0;k<datec[i][j];k++)
							{
								if((ground_db[i].game[j].dates[k].date)==date_srch)
								{
									int flag=0;
									for(l=0;l<timingc[i][j][k] && flag==0;l++)
									{
										if(ground_db[i].game[j].dates[k].times[l]<=time_srch && ground_db[i].game[j].dates[k].timee[l]>=time_srch)
										{
											flag=1;
										}
										
									}
									if(flag==0)
									{
										index[x] = i;
											x++;
									}
							    }
							}
						}
					}
				}
			}
		}
	}			
	

	if(x==0){ 
		return FAILURE;
	}

	int sorted=0;
	struct Ground_db temp;
	for(i=0; i<x && sorted==0; i++){
		sorted = 1;
		for(j=1; j<x-i; j++){
			int p=strcmp(ground_db[index[j-1]].state, ground_db[index[j]].state);
			if(p>0){
				temp = ground_db[index[j-1]];
				ground_db[index[j-1]] = ground_db[index[j]];
				ground_db[index[j]] = temp ; 
				sorted = 0;
			}
			if(p==0){
				int citys = strcmp(ground_db[index[j-1]].city, ground_db[index[j]].city);
				if(citys>0){
					temp = ground_db[index[j-1]];
					ground_db[index[j-1]] = ground_db[index[j]];
					ground_db[index[j]] = temp ; 
					sorted = 0;
				}
			}
		}
	}

	printf("\nGrounds Available are : \n");
	for(i=0; i<x; i++){
		printf("%s\n", ground_db[index[i]].state);
		printf("%s\n", ground_db[index[i]].city);
		printf("%s\n", ground_db[index[i]].ground_name);
	}
	return SUCCESS;
}

int UniqueSports(int nod, int count[]){
	char ground_nm[15], in_city[15];
	int ground_index, index[5]={0},x=0,i,j; 
	printf("\nGround Name : ");
	scanf("%s", ground_nm);
	printf("\nCity : ");
	scanf("%s", in_city);
	for(i=0; i<=nod; i++){
		if(strcmp(ground_db[i].city, in_city)==0){
			index[x] = i;
			x++;		
			if(strcmp(ground_db[i].ground_name, ground_nm)==0){
				ground_index = i; 	
				index[x]=0;
				x -= 1;
			}	
		}
	}
	printf("\nIn %s unique games are : \n", in_city);
	int uniq=1, k=0;
	for(i=0; i<x && k<count[ground_index]; i++){
		while(k<count[ground_index]){
			uniq = 1;
			for(j=0; j<count[index[i]]; j++){
				if(strcmp(ground_db[ground_index].game[k].game_name, ground_db[index[i]].game[j].game_name)==0){
					uniq=0;
				}
			}
			if(uniq==1){
				printf("\n%s", ground_db[ground_index].game[k].game_name);
			}	
			k++;
		}
	}
	return SUCCESS;
}


int sportwithground(int nodb,int count[])					//nodb-no. of database entries,count array denotes no. of games in each ground
   	{
		int c=0,i,j,flag,k=0;
		char spname[15],gname[5][20]={0};
		printf("\n enter the name of sport \n");
		scanf("%s",spname);
		for(i=0;i<=nodb;i++)
		{
			flag=0;
			for(j=0;j<count[i] && flag==0;j++)
			{
				if(strcmp(ground_db[i].game[j].game_name,spname)==0)
				{
					strcpy(gname[k],ground_db[i].ground_name);
					k++;		//printf("%s\n",ground_db[i].ground_name);
					flag=1;
					c++;			
				}			
			}			
	   }
	  
	   	int sorted=0;
	   	char temp[20];
	   for(i=0;i<k && sorted==0;i++)
	   {
	   		sorted=1;
	   		for(j=1;j<k-i;j++)
	   		{
	   			if(strcmp(gname[j-1],gname[j])>0)
				   {
						 strcpy(temp,gname[j-1]);
						 strcpy(gname[j-1],gname[j]);
						 strcpy(gname[j],temp);
						 sorted=0;
				   }	
		    }
		}
		 for(i=0;i<k;i++)
			printf("%s\n",gname[i]); 
		
	   return c;  		
   }
   
   int ClashofMatches(int nod, int co[]){
	int flag=1, c=0, index_grnd[5]={0}, index_gm[5]={0}, x=0, y=0, dat, clashed=-1,i,j,k;
	char gmClash[15], ground[20], found_grnd[20];

	printf("\nEnter game to check : ");
	scanf("%s", gmClash);
	while(flag==1){
		printf("\nEnter ground in list : \n");
		scanf("%s", ground);
		for(i=0; i<=nod; i++){
			if(strcmp(ground_db[i].ground_name, ground)==0){
				index_grnd[x]=i;
				x++;
				for(j=0; j<co[i]; j++){
					if(strcmp(ground_db[i].game[j].game_name, gmClash)==0){
						index_gm[y]=j;
						y++;
					}
				}
			}
		}
		printf("\nPress 0 to stop\n");
		scanf("%d", &flag);
	}

	printf("\nEnter date : ");
	scanf("%d", &dat);

	for(i=0; i<x; i++){
		flag=0;
		for(j=0; j<y; j++){
			for(k=0; k<datec[index_grnd[i]][index_gm[j]] && flag==0; k++){
				if(ground_db[index_grnd[i]].game[index_gm[j]].dates[k].date == dat){
					clashed++;
					if(clashed==0)
					{
						strcpy(found_grnd, ground_db[index_grnd[i]].ground_name);
					}
					else if(clashed==1)
					{
						printf("%s\n%s\n", found_grnd, ground_db[index_grnd[i]].ground_name);
					}
					else if(clashed>1)
					{
						printf("%s\n", ground_db[index_grnd[i]].ground_name);
					}
					flag=1;
				}
			}
		}
	}
	
	return clashed; 

}

   
   int sortinpriceforagame(int nod,int count[])
   {
   		int i,j,orgdate,timeduration,k,c=0,l,hhr[5];			//orgdate is organising date
		char spname[15],gname[5][20],gtemp[20];
	//	for(i=0;i<=nod;i++)
		//	printf("%d\n",count[i]);
		printf("\n Enter the sport you want to check for");
		scanf("%s",spname);
		printf("\nEnter the date");
		scanf("%d",&orgdate);
		printf("\n Enter time duration");
		scanf("%d",&timeduration);
			for(i=0;i<=nod;i++)
		{
			for(j=0;j<count[i];j++)
			{
			//	printf("%s\n",ground_db[i].game[j].game_name);
				if(strcmp(ground_db[i].game[j].game_name,spname)==0)
				{
					for(k=0;k<datec[i][j];k++)
					{
						if((ground_db[i].game[j].dates[k].date)==orgdate)
						{
							int flag=0;
							for(l=0;l<timingc[i][j][k] && flag==0;l++)
							{
				
									hhr[c]=ground_db[i].game[j].hourly_rate;
									strcpy(gname[c],ground_db[i].ground_name);
									flag=1;
									c++;
							
							}		
					    }
					}
				}
			}
		}
	//	printf("%d\n",c);
		for(i=0;i<c;i++)
		{
			for(j=1;j<c-i;j++)
			{
				if(hhr[j-1]*timeduration>hhr[j]*timeduration)
				{
					int temp=hhr[j-1];
					strcpy(gtemp,gname[j-1]);
					hhr[j-1]=hhr[j];
					strcpy(gname[j-1],gname[j]);
					hhr[j]=temp;
					strcpy(gname[j],gtemp);
				}
			}
		}
		for(i=0;i<c;i++)
			printf("%s\n",gname[i]);
		return c; 	
   }
   
   int givelistofgroundhavingonematch(int nod,int count[])
   {
   		int nog,i,j,k,dno,l,c=0;									//nog-no. of games,dno-date no.
   		char gname[15],cname[15];
   		printf("\nEnter no. of games in your game list");
   		scanf("%d",&nog);
   		printf("\nEnter city name");
   		scanf("%s",cname);
   		printf("\nEnter date");
   		scanf("%d",&dno);
   		for(i=0;i<nog;i++)
   		{
   			printf("\n Enter name of game");
   			scanf("%s",gname);										
   			for(j=0;j<=nod;j++)
   			{
   				if(strcmp(ground_db[j].city,cname)==0)
   				{
   					printf("%d\n",j);
   					for(k=0;k<count[j];k++)
					   {
							if(strcmp(ground_db[j].game[k].game_name,gname)==0)
							{
									printf("%d\n",k);
								for(l=0;l<datec[j][k];l++)
								{
									printf("%d\n",ground_db[j].game[k].dates[l].date);
									if(ground_db[j].game[k].dates[l].date==dno)
									{
											printf("%d\n",l);
										if(timingc[j][k][l]>=1)
										{
											printf("%s\n",ground_db[j].ground_name);
											c++;		
										}		
									}		
								}		
						   }   	
					   }	
				}
		    }
		 		
		}
		return c;
   		
   }
   
   int givelistofgroundhavingkmatches(int nod,int count[])
   {
   		int nog,i,j,k,dno,l,c=0,nom;									//nog-no. of games,dno-date no.
   		char gname[15],cname[15];
   		printf("\nEnter no. of games in your game list");
   		scanf("%d",&nog);
   		printf("\nEnter city name");
   		scanf("%s",cname);
   		printf("\nEnter date");
   		scanf("%d",&dno);
   		printf("\nEnter value of K");
   		scanf("%d",&nom);
   		for(i=0;i<nog;i++)
   		{
   			printf("\n Enter name of game");
   			scanf("%s",gname);										
   			for(j=0;j<=nod;j++)
   			{
   				if(strcmp(ground_db[j].city,cname)==0)
   				{
   					printf("%d\n",j);
   					for(k=0;k<count[j];k++)
					   {
							if(strcmp(ground_db[j].game[k].game_name,gname)==0)
							{
									printf("%d\n",k);
								for(l=0;l<datec[j][k];l++)
								{
									printf("%d\n",ground_db[j].game[k].dates[l].date);
									if(ground_db[j].game[k].dates[l].date==dno)
									{
											printf("%d\n",l);
										if(timingc[j][k][l]>=nom)
										{
											printf("%s\n",ground_db[j].ground_name);
											c++;		
										}		
									}		
								}		
						   }   	
					   }	
				}
		    }
		 		
		}
		return c;
   		
   }
 

int main(){
	// void init();
	// struct Ground_db ground_db[5]s ;
	init(2);
	
																				//array co for checking how many games in each ground
		int status, ch, num=0,countsport[5]={0},res;	                                   	// char ground[20], city_nm[15]
	strcpy(ground_db[0].ground_name,"patel_stadium");               				//datec is an array containing the count of no. dates of each game          
	strcpy(ground_db[0].city,"ajmer");
	strcpy(ground_db[0].state,"rajasthan");
	
	strcpy(ground_db[0].game[0].game_name,"football");
	ground_db[0].game[0].dates[0].date=23;
	ground_db[0].game[0].dates[0].times[0]=1400;
	ground_db[0].game[0].dates[0].timee[0]=1600;
    ground_db[0].game[0].dates[0].times[1]=1700;
    ground_db[0].game[0].dates[0].timee[1]=1900;
   	ground_db[0].game[0].dates[0].times[2]=2000;
   	ground_db[0].game[0].dates[0].timee[2]=2200;
   	timingc[0][0][0]=3;
    ground_db[0].game[0].dates[1].date=25;
   	ground_db[0].game[0].dates[1].times[0]=1400;
	ground_db[0].game[0].dates[1].timee[0]=1600;
    ground_db[0].game[0].dates[1].times[1]=1700;
    ground_db[0].game[0].dates[1].timee[1]=1900;
   	ground_db[0].game[0].dates[1].times[2]=2000;
   	ground_db[0].game[0].dates[1].timee[2]=2200;
   	timingc[0][0][1]=3;
   	ground_db[0].game[0].dates[2].date=28;
   	ground_db[0].game[0].dates[2].times[0]=1400;
	ground_db[0].game[0].dates[2].timee[0]=1600;
    ground_db[0].game[0].dates[2].times[1]=1700;
    ground_db[0].game[0].dates[2].timee[1]=1900;
   	ground_db[0].game[0].dates[2].times[2]=2000;
   	ground_db[0].game[0].dates[2].timee[2]=2200;
   	timingc[0][0][2]=3;
   	ground_db[0].game[0].hourly_rate=1000;
   	datec[0][0]=3;
   	
	strcpy(ground_db[0].game[1].game_name,"handball");
		ground_db[0].game[1].dates[0].date=20;
	ground_db[0].game[1].dates[0].times[0]=1400;
	ground_db[0].game[1].dates[0].timee[0]=1630;
    ground_db[0].game[1].dates[0].times[1]=1700;
    ground_db[0].game[1].dates[0].timee[1]=1930;
   	ground_db[0].game[1].dates[0].times[2]=2000;
   	ground_db[0].game[1].dates[0].timee[2]=2230;
   	timingc[0][1][0]=3;
    ground_db[0].game[1].dates[1].date=25;
    ground_db[0].game[1].dates[1].times[0]=1400;
	ground_db[0].game[1].dates[1].timee[0]=1630;
    ground_db[0].game[1].dates[1].times[1]=1700;
    ground_db[0].game[1].dates[1].timee[1]=1930;
   	ground_db[0].game[1].dates[1].times[2]=2000;
   	ground_db[0].game[1].dates[1].timee[2]=2230;
   	timingc[0][1][1]=3;
   	ground_db[0].game[1].dates[2].date=27;
   ground_db[0].game[1].dates[2].times[0]=1400;
	ground_db[0].game[1].dates[2].timee[0]=1630;
    ground_db[0].game[1].dates[2].times[1]=1700;
    ground_db[0].game[1].dates[2].timee[1]=1930;
   	ground_db[0].game[1].dates[2].times[2]=2000;
   	ground_db[0].game[1].dates[2].timee[2]=2230;
   	timingc[0][1][2]=3;
   	ground_db[0].game[1].hourly_rate=500;
   	datec[0][1]=3;
   	
	strcpy(ground_db[0].game[2].game_name,"squash");
	ground_db[0].game[2].dates[0].date=23;
	ground_db[0].game[2].dates[0].times[0]=1200;
	ground_db[0].game[2].dates[0].timee[0]=1300;
    ground_db[0].game[2].dates[0].times[1]=1500;
    ground_db[0].game[2].dates[0].timee[1]=1600;
   	ground_db[0].game[2].dates[0].times[2]=2000;
   	ground_db[0].game[2].dates[0].timee[2]=2100;
   	timingc[0][2][0]=3;
    ground_db[0].game[2].dates[1].date=29;
   ground_db[0].game[2].dates[1].times[0]=1200;
	ground_db[0].game[2].dates[1].timee[0]=1300;
    ground_db[0].game[2].dates[1].times[1]=1500;
    ground_db[0].game[2].dates[1].timee[1]=1600;
   	ground_db[0].game[2].dates[1].times[2]=2000;
   	ground_db[0].game[2].dates[1].timee[2]=2100;
   	timingc[0][2][1]=3;
   	ground_db[0].game[2].dates[2].date=31;
   ground_db[0].game[2].dates[2].times[0]=1200;
	ground_db[0].game[2].dates[2].timee[0]=1300;
    ground_db[0].game[2].dates[2].times[1]=1500;
    ground_db[0].game[2].dates[2].timee[1]=1600;
   	ground_db[0].game[2].dates[2].times[2]=2000;
   	ground_db[0].game[2].dates[2].timee[2]=2100;
   	timingc[0][2][2]=3;
   	ground_db[0].game[2].hourly_rate=500;
   	datec[0][2]=3;
   	countsport[0]=3;															
   	
   	strcpy(ground_db[1].ground_name,"gandhi_stadium");
	strcpy(ground_db[1].city,"udaipur");
	strcpy(ground_db[1].state,"maharashtra");
	
	strcpy(ground_db[1].game[0].game_name,"hockey");
		ground_db[1].game[0].dates[0].date=23;
	ground_db[1].game[0].dates[0].times[0]=1400;
	ground_db[1].game[0].dates[0].timee[0]=1600;
    ground_db[1].game[0].dates[0].times[1]=1700;
    ground_db[1].game[0].dates[0].timee[1]=1900;
   	ground_db[1].game[0].dates[0].times[2]=2000;
   	ground_db[1].game[0].dates[0].timee[2]=2200;
   	timingc[1][0][0]=3;
    ground_db[1].game[0].dates[1].date=25;
   	ground_db[1].game[0].dates[1].times[0]=1400;
	ground_db[1].game[0].dates[1].timee[0]=1600;
    ground_db[1].game[0].dates[1].times[1]=1700;
    ground_db[1].game[0].dates[1].timee[1]=1900;
   	ground_db[1].game[0].dates[1].times[2]=2000;
   	ground_db[1].game[0].dates[1].timee[2]=2200;
   	timingc[1][0][1]=3;
   	ground_db[1].game[0].dates[2].date=28;
   	ground_db[1].game[0].dates[2].times[0]=1400;
	ground_db[1].game[0].dates[2].timee[0]=1600;
    ground_db[1].game[0].dates[2].times[1]=1700;
    ground_db[1].game[0].dates[2].timee[1]=1900;
   	ground_db[1].game[0].dates[2].times[2]=2000;
   	ground_db[1].game[0].dates[2].timee[2]=2200;
   	timingc[1][0][2]=3;
   	ground_db[1].game[0].hourly_rate=1000;
   	datec[1][0]=3;
   	
	strcpy(ground_db[1].game[1].game_name,"volleyball");
	ground_db[1].game[1].dates[0].date=20;
	ground_db[1].game[1].dates[0].times[0]=1430;
	ground_db[1].game[1].dates[0].timee[0]=1630;
    ground_db[1].game[1].dates[0].times[1]=1730;
    ground_db[1].game[1].dates[0].timee[1]=1930;
   	ground_db[1].game[1].dates[0].times[2]=2030;
   	ground_db[1].game[1].dates[0].timee[2]=2230;
   	timingc[1][1][0]=3;
    ground_db[1].game[1].dates[1].date=25;
    ground_db[1].game[1].dates[1].times[0]=1430;
	ground_db[1].game[1].dates[1].timee[0]=1630;
    ground_db[1].game[1].dates[1].times[1]=1730;
    ground_db[1].game[1].dates[1].timee[1]=1930;
   	ground_db[1].game[1].dates[1].times[2]=2030;
   	ground_db[1].game[1].dates[1].timee[2]=2230;
   	timingc[1][1][1]=3;
   	ground_db[1].game[1].dates[2].date=27;
   ground_db[1].game[1].dates[2].times[0]=1430;
	ground_db[1].game[1].dates[2].timee[0]=1630;
    ground_db[1].game[1].dates[2].times[1]=1730;
    ground_db[1].game[1].dates[2].timee[1]=1930;
   	ground_db[1].game[1].dates[2].times[2]=2030;
   	ground_db[1].game[1].dates[2].timee[2]=2230;
   	timingc[1][1][2]=3;
   	ground_db[1].game[1].hourly_rate=750;
   	datec[1][1]=3;
   	
	strcpy(ground_db[1].game[2].game_name,"yatching");
	ground_db[1].game[2].dates[0].date=23;
	ground_db[1].game[2].dates[0].times[0]=1200;
	ground_db[1].game[2].dates[0].timee[0]=1300;
    ground_db[1].game[2].dates[0].times[1]=1500;
    ground_db[1].game[2].dates[0].timee[1]=1600;
   	ground_db[1].game[2].dates[0].times[2]=2000;
   	ground_db[1].game[2].dates[0].timee[0]=2100;
   	timingc[1][2][0]=3;
    ground_db[1].game[2].dates[1].date=29;
    ground_db[1].game[2].dates[1].times[0]=1200;
	ground_db[1].game[2].dates[1].timee[0]=1300;
    ground_db[1].game[2].dates[1].times[1]=1500;
    ground_db[1].game[2].dates[1].timee[1]=1600;
   	ground_db[1].game[2].dates[1].times[2]=2000;
   	ground_db[1].game[2].dates[1].timee[0]=2100;
   	timingc[1][2][1]=3;
   	ground_db[1].game[2].dates[2].date=31;
    ground_db[1].game[2].dates[2].times[0]=1200;
	ground_db[1].game[2].dates[2].timee[0]=1300;
    ground_db[1].game[2].dates[2].times[1]=1500;
    ground_db[1].game[2].dates[2].timee[1]=1600;
   	ground_db[1].game[2].dates[2].times[2]=2000;
   	ground_db[1].game[2].dates[2].timee[2]=2100;
   	timingc[1][2][2]=3;
   	ground_db[1].game[2].hourly_rate=500;
   	datec[1][2]=3;
   	countsport[1]=3;
   	
   	strcpy(ground_db[2].ground_name,"patel_stadium");
	strcpy(ground_db[2].city,"udaipur");
	strcpy(ground_db[2].state,"rajasthan");
	
	strcpy(ground_db[2].game[0].game_name,"volleyball");
	ground_db[2].game[0].dates[0].date=20;
	ground_db[2].game[0].dates[0].times[0]=1400;
	ground_db[2].game[0].dates[0].timee[0]=1600;
    ground_db[2].game[0].dates[0].times[1]=1700;
    ground_db[2].game[0].dates[0].timee[1]=1900;
   	ground_db[2].game[0].dates[0].times[2]=2000;
   	ground_db[2].game[0].dates[0].timee[2]=2200;
   	timingc[2][0][0]=3;
    ground_db[2].game[0].dates[1].date=25;
   	ground_db[2].game[0].dates[1].times[0]=1400;
	ground_db[2].game[0].dates[1].timee[0]=1600;
    ground_db[2].game[0].dates[1].times[1]=1700;
    ground_db[2].game[0].dates[1].timee[1]=1900;
   	ground_db[2].game[0].dates[1].times[2]=2000;
   	ground_db[2].game[0].dates[1].timee[2]=2200;
   	timingc[2][0][1]=3;
   	ground_db[2].game[0].dates[2].date=28;
   	ground_db[2].game[0].dates[2].times[0]=1400;
	ground_db[2].game[0].dates[2].timee[0]=1600;
    ground_db[2].game[0].dates[2].times[1]=1700;
    ground_db[2].game[0].dates[2].timee[1]=1900;
   	ground_db[2].game[0].dates[2].times[2]=2000;
   	ground_db[2].game[0].dates[2].timee[2]=2200;
   	timingc[2][0][2]=3;
   	ground_db[2].game[0].hourly_rate=200;
   	datec[2][0]=3;
   	
	strcpy(ground_db[2].game[1].game_name,"wrestling");
		ground_db[2].game[1].dates[0].date=20;
	ground_db[2].game[1].dates[0].times[0]=1400;
	ground_db[2].game[1].dates[0].timee[0]=1630;
    ground_db[2].game[1].dates[0].times[1]=1700;
    ground_db[2].game[1].dates[0].timee[1]=1930;
   	ground_db[2].game[1].dates[0].times[2]=2000;
   	ground_db[2].game[1].dates[0].timee[2]=2230;
   	timingc[2][1][0]=3;
    ground_db[2].game[1].dates[1].date=25;
    ground_db[2].game[1].dates[1].times[0]=1400;
	ground_db[2].game[1].dates[1].timee[0]=1630;
    ground_db[2].game[1].dates[1].times[1]=1700;
    ground_db[2].game[1].dates[1].timee[1]=1930;
   	ground_db[2].game[1].dates[1].times[2]=2000;
   	ground_db[2].game[1].dates[1].timee[2]=2230;
   	timingc[2][1][1]=3;
   	ground_db[2].game[1].dates[2].date=27;
   ground_db[2].game[1].dates[2].times[0]=1400;
	ground_db[2].game[1].dates[2].timee[0]=1630;
    ground_db[2].game[1].dates[2].times[1]=1700;
    ground_db[2].game[1].dates[2].timee[1]=1930;
   	ground_db[2].game[1].dates[2].times[2]=2000;
   	ground_db[2].game[1].dates[2].timee[2]=2230;
   	timingc[2][1][2]=3;
   	ground_db[2].game[1].hourly_rate=1000;
   	datec[2][1]=3;
   	
	strcpy(ground_db[2].game[2].game_name,"yakpolo");
	ground_db[2].game[2].dates[0].date=23;
	ground_db[2].game[2].dates[0].times[0]=1200;
	ground_db[2].game[2].dates[0].timee[0]=1300;
    ground_db[2].game[2].dates[0].times[1]=1500;
    ground_db[2].game[2].dates[0].timee[1]=1600;
   	ground_db[2].game[2].dates[0].times[2]=2000;
   	ground_db[2].game[2].dates[0].timee[2]=2100;
   	timingc[2][2][0]=3;
    ground_db[2].game[2].dates[1].date=29;
   ground_db[2].game[2].dates[1].times[0]=1200;
	ground_db[2].game[2].dates[1].timee[0]=1300;
    ground_db[2].game[2].dates[1].times[1]=1500;
    ground_db[2].game[2].dates[1].timee[1]=1600;
   	ground_db[2].game[2].dates[1].times[2]=2000;
   	ground_db[2].game[2].dates[1].timee[2]=2100;
   	timingc[2][2][1]=3;
   	ground_db[2].game[2].dates[2].date=31;
   ground_db[2].game[2].dates[2].times[0]=1200;
	ground_db[2].game[2].dates[2].timee[0]=1300;
    ground_db[2].game[2].dates[2].times[1]=1500;
    ground_db[2].game[2].dates[2].timee[1]=1600;
   	ground_db[2].game[2].dates[2].times[2]=2000;
   	ground_db[2].game[2].dates[2].timee[2]=2100;
   	timingc[2][2][2]=3;
   	ground_db[2].game[2].hourly_rate=750;
   	datec[2][2]=3;
   	countsport[2]=3;				
	
   	
   	
	int i=2;										//variable i is denoting the no. of grounds present(index)

	sortGround(i,countsport);
	printf("\nA. Display Data\na.get info of ground\nb. Add Ground Record\nc. Delete Ground Record\nd. Add Sport\ne. Delete Sport\nf.Update ground recoerd\n");
	printf("g.fixtures happening in the city\nh.fixtures happening in the state\nj.fixtures sorted according to state\n");
	printf("k.Available grounds\nl.Unique Sports on ground\nm.finding ground according to sports\nn.FindlocationsforGameEvent\no. ground names to hold the game you want\n");
	printf("p.gorund names for your timings\nq.clash of matches\nr.give list of ground having one match\ns.give list of ground having k matches\nt.to get the grounds according to price rate\n");
	char choice;
while(1){
		scanf("%c", &choice);
		switch(choice){
			case 'A': 	display(i,countsport);
						break;
						
			case 'a':   status = getGroundInfo(i, countsport);
						if(status==0){
							printf("No grounds found !!\n");
						}
						break;
																			//try learning enum
			case 'b': 	status = addGround(i+1,countsport);	
						if(status == 1)
						{	
						   	printf("SUCCESS :)\n");
						   	i++;
						   //	sortGround(i);
						}
						else
							printf("FAILURE :(\n");
						break;
			
			case 'c' :  status = deleteGround(i);
						if(status == 1){
							i--;
							printf("SUCCESS :)\n");
						}
						else	
							printf("FAILURE :(\n");
						break;
							
			case 'd' :  	res=addSport(i,countsport);
						 	if(res!=-1)
						 	{
							printf("SUCCESS :)\n");
							countsport[res]++;
						    }
							else
							printf("FAILURE :(\n");
				
						break;
					
			case 'e':  res=deleteSport(i,countsport);
						if(res==1)
							printf("SUCCESS :)\n");
						else
							printf("FAILURE :(\n)");
							break;
							
			case 'f':  status = updateGround(i,countsport);
						if(status == 1){
							printf("Updated !!\n");
						}
						else
							printf("Not Found\n");
						break;
						
			case 'g':	status = getFixturesinCity(i, countsport);
						if(status == 0){
							printf("No games are scheduled...");
						}
						break;

			case 'h':   getFixturesinState(i, countsport);
						sortGround(i, countsport);
						break;		

			case 'i':   getFixturesortedOnDate(i, countsport);
						break;					
			
			case 'j': statesort(i);
						printf("!!!SORTING DONE!!!\n");
						break;
						
			case 'k': 	status = isAvailable(i, countsport);
						if(status==0){
							printf("Not Available\n");
						}
						sortGround(i, countsport);
						break;
						
			case 'l' : 	UniqueSports(i, countsport);
						break;				
						
			case 'm': res=sportwithground(i,countsport);
						if(res==0)
							printf("\nNone of the ground is organising this sport");
							break;
			
			case 'n':res= FindlocationsforGameEvent(i,countsport);
						if(res==0)
							printf("\nNone of the ground is organising this sport at enterd date and time");
						break;
						
			case 'o':	status = FindlocationsforGame(i,countsport);
						if(status == 0)
							printf("\nNo grounds available !!");
						break;
						
			case 'p': 	status = FindlocationsforGameInTimeRange(i, countsport);
						if(status==0){
							printf("No grounds available...\n");
						}
						break;
						
			case 'q':   status = ClashofMatches(i, countsport);
						if(status==0){
							printf("\nNo clash in matches...\n");
						}
						break;
						
			case 'r': res=givelistofgroundhavingonematch(i,countsport);
						if(res==0)
							printf("\n Sorry we are not organising any of your entered game in this city ");  
						break;
						
			case 's': res=givelistofgroundhavingkmatches(i,countsport);
						if(res==0)
							printf("\n Sorry we are not organising any of your entered game in this city ");  
						break;				
						
			case't':res=sortinpriceforagame(i,countsport);//make changes
						if(res==0)
							printf("\nNone of the ground is organising this sport at enterd date and time");
						break;
						
			case '0':	printf("\nThanks ... GoodBye....\n");
						printf("\nSee you again \n");
						exit(0);
						
		}
		// num = count;
	
	}

	return 0;
}
