#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
   unsigned char RGB[3]; // RGB
}RGBPixel;

typedef struct{
	int width; 
    int height;
	RGBPixel **pixels;
	int max; // for error check. max 255.
}RGB_Image; 

typedef struct{
	    unsigned char Gray;
}GrayPixel;

typedef struct{
	    int width;
		int height;
		GrayPixel **pixels;
		int max;
}Gray_Image;

int readImage(char* fileName,RGB_Image* image);

int writeRGBImage(char* fileName,RGB_Image* image);

int writeGrayImage(char* fileName,Gray_Image* image);

int resize(RGB_Image* src,RGB_Image* dst, char* cmd);

int rotate(RGB_Image* src,RGB_Image* dst, char* cmd);

int flip_RGB(RGB_Image* src, RGB_Image* dst, char* cmd);

void grayScale(RGB_Image* src,Gray_Image* dst);

void colorSmooth(RGB_Image* src,RGB_Image* outsrc);

int readImage(char* fileName,RGB_Image* image);

int main(int argc,char **argv)
{
	RGB_Image old;
	RGB_Image new;
	Gray_Image gray;
	printf("read: %d\n",readImage(argv[1],&old));
	char* cmd=(char*)malloc(sizeof(char)*10);
	//printf("write: %d\n",writeImage("TestResult.ppm",&old));
	// You can test if writing Image is succcessful.



	printf("Input flip cmd : ");
	scanf("%s",cmd);
	printf("cmd : %s\n",cmd);
	flip_RGB(&old,&new,cmd);
	printf("writing Flipimage: %d\n",writeRGBImage("AfterFlip.ppm",&new));
	//Individual case : Testing Flip.

	
	printf("Input resize cmd : ");
	scanf("%s",cmd);
	printf("cmd : %s\n",cmd);
	resize(&old,&new,cmd);
	printf("writing resized image: %d\n",writeRGBImage("AfterResize.ppm",&new));
	//Individual case : Testing Resize.	

	printf("GrayScaling...\n");
	grayScale(&old,&gray);
	printf("writting grayscaled image: %d\n",writeGrayImage("AfterGrayscale.ppm",&gray));
	//Individual case : Testing Grayscale.

	printf("Input rotate cmd : ");
	scanf("%s",cmd);
	printf("cmd : %s\n",cmd);
	rotate(&old,&new,cmd);
	printf("writting rotated image: %d\n",writeRGBImage("AfterRotate.ppm",&new));
	//Individual case : Testing Rotate.

	
	printf("smoothing...\n");
	colorSmooth(&old,&new);
	printf("writting smoothed image: %d\n",writeRGBImage("AfterSmooth.ppm",&new));
	// Individual case : Testing Smoothe.
	


	/*	
	int sel[5]={0,}; // Initialization; For case your sel is not available.
	int i; // For for
	int num; // number of action
	int gray_switch=0; // grayScale ON or OFF?

	RGB_Image* seq=(RGB_Image*)malloc(sizeof(RGB_Image)*6); // Image arrays, for cascading Image Edit
	seq[0]=old; // First image;Initialization


	printf("input number of actions you want to take\n"); // Num of actions
	scanf("%d",&num);
	printf("You can input actions you want, but you must input grayscale at LAST\n"); // Input Restrictions!!!
	for(i=0;i<num;i++) // Cascading Image Edit
	{
		printf(" 1. resize	2. rotate 	3. flip		4. smooth	5.grayscale\n");
		scanf("%d",&sel[i]); // You can select 
		switch(sel[i]) // For each Input behavior
		{
			case 0:
				{
					printf("Selection Error!\n");
					break; // In Case you input wrong number
				}
			case 1:
				{
					printf("You selected resize\n");
					printf("Input cmd : ");
					scanf("%s",cmd); // input cmd
					printf("Your cmd: %s\n",cmd); // cmd confirm
					resize(&seq[i],&seq[i+1],cmd); // action
					printf("resize complete\n"); // done
					break; 
					// resizing, from seq[0] (==old) to seq[1] (new)
				}
			case 2:
				{
					printf("You selected rotate\n");
					printf("Input cmd : ");
					scanf("%s",cmd);
					printf("Your cmd: %s\n",cmd);
					rotate(&seq[i],&seq[i+1],cmd);
					printf("rotate complete\n");
					break; // roatation
				}
			case 3:
				{
					printf("You selected flip\n");
					printf("Input cmd : ");
					scanf("%s",cmd);
					printf("Your cmd: %s\n",cmd);
					flip_RGB(&seq[i],&seq[i+1],cmd);
					printf("flip complete\n");
					break; // flip
				}
			case 4:
				{
					printf("You selected smooth\n");
					colorSmooth(&seq[i],&seq[i+1]);
					printf("color smooth complete\n");
					break; // smoothing
				}
			case 5:
				{
					printf("You selected grayscale\n");
					gray_switch=1; // if you input grayScale, flag(switch) is ON
					// NOTE that here you don't manipulate the image right here, but done later at the end
					break; // grayscaling
				}
			default :
				{
					printf("Selection Error!\n");
					break; // In Case you input wrong number
				}
		}
	}
	// NOTE : If gray switch is ON, your seq[]  manipulation is done at seq[i-1]
	// This means, you manipulate 1 time less when you gray scale. your final manipulation is done later
	// Else, your manipulation is done at seq[i].

	if(gray_switch) // If you have to grayScale
	{
		grayScale(&seq[i-1],&gray); 
		printf("Writing final image : %d\n",writeGrayImage("Final.ppm",&gray));
	}
	// Final manipulation (grayscale) 

	else // If you have no grayScale
		printf("Writing final image : %d\n",writeRGBImage("Final.ppm",&seq[i])); // just follow the order

	// Here, keypoint is Grayscale, that manipulation {1,2,3,4} and {5} are independent.
	// That means, you can grayscale at the end. And tha means, input restriction occurs.
	// Why? If not you should make pair of manipulation functions for Gray_Image type.

	*/

	return 0;
}

int readImage(char* fileName,RGB_Image* image)
{
	FILE* fp;
	char c1,c2;
	int temp=-1;

	if(fileName==NULL)
	{
		fprintf(stderr,"FileProblem\n");
		return 0;
	}// FileProblem

	fp=fopen(fileName,"rb");
	
	if(fp==NULL)
	{
		fprintf(stderr,"Cannot Open The File %s !\n",fileName);
		return 0;
	} // File Problem

	fscanf(fp,"%c%c\n",&c1,&c2);
	if(c1!='P' || c2!='6')
	{
		fprintf(stderr,"Format Is Not A P6 Format!\n");
		return 0;
	} // Magic Number Problem
	
	fscanf(fp,"%d %d\n",&(image->width),&(image->height)); 
	fscanf(fp,"%d\n",&(image->max)); 

	if(image->max!=255)
	{
		fprintf(stderr,"Problem With Maxvalue\n");
		return 0;
	} // Max Problem

	image->pixels=(RGBPixel**)malloc(sizeof(RGBPixel*)*(image->height));
	for(int i=0;i<image->height;i++)
		image->pixels[i]=(RGBPixel*)malloc(sizeof(RGBPixel)*(image->width));
	// Memory Allocation

	for(int j=0;j<(image->height);j++)
	{
		for(int k=0;k<(image->width);k++)
		{
			for(int l=0;l<3;l++)
				fread(&(image->pixels[j][k].RGB[l]),sizeof(unsigned char),1,fp);
		}
	}
	// Reading image
	fclose(fp);

	return 1;
}
	
int writeRGBImage(char* fileName,RGB_Image* image)
{
	FILE* fp;

	fp=fopen(fileName,"w");
	if(fp==NULL)
	{
		fprintf(stderr,"Error Creating File!\n");
		return 0;
	}
	//File Problem
	
	fprintf(fp,"%c%c\n",'P','3');
	fprintf(fp,"%d %d\n",image->width,image->height);
	fprintf(fp,"%d\n",255);
	// Copying the basic info

	for(int i=0;i<image->height;i++)
	{
		for(int j=0;j<image->width;j++)
		{
			for(int k=0;k<3;k++)
				fprintf(fp,"%d ",image->pixels[i][j].RGB[k]); // Be aware of RGB array
		}
		fprintf(fp,"\n");
	}
	// Writing image with format
	
	fclose(fp);

	return 1; // If success, return 1
}


int writeGrayImage(char* fileName,Gray_Image* image)
{
	FILE *fp;
	fp=fopen(fileName,"w");
	if(fp==NULL)
	{
		fprintf(stderr,"Error Creating File!\n");
		return 0;
	}
				
	fprintf(fp,"%c%c\n",'P','2');
	fprintf(fp,"%d %d\n",image->width,image->height);
	fprintf(fp,"%d\n",255);
	for(int i=0;i<image->height;i++)
	{
		for(int j=0;j<image->width;j++)
			fprintf(fp,"%d ",image->pixels[i][j].Gray); // Only .Gray so don't need array
		fprintf(fp,"\n");
	}
	fclose(fp);
	// Same as RGB Image, but gray type
	return 1; // If success, return 1
}

int flip_RGB(RGB_Image* src,RGB_Image* dst,char* cmd)
{
	int y=src->height;
	int x=src->width;

	dst->height=src->height;
	dst->width=src->width;
	dst->max=src->max;
	
	dst->pixels=(RGBPixel**)malloc(sizeof(RGB_Image*)*dst->height);
	for(int i=0;i<dst->height;i++)
		dst->pixels[i]=(RGBPixel*)malloc(sizeof(RGB_Image)*dst->width);
	// Memmory Allocation for new flipped RGBImage

		if(!strcmp(cmd,"horizon")) // case horizon
		{
			for(int i=0;i<src->height;i++)
				dst->pixels[i]=src->pixels[src->height-i-1]; // You only have care 'row'
			return 1;
		} // Copy the changed image to dst

		if(!strcmp(cmd,"vertical")) // case vertical
		{	
			for(int i=0;i<src->height;i++)
			{
				for(int j=0;j<src->width;j++)
					dst->pixels[i][j]=src->pixels[i][src->width-j-1]; // You have to care about 'row' and 'col'
			}
			return 1;
		} // Copty the changed image to dst


		return 0; // return 1 only when it success.
}
		
int resize(RGB_Image* src,RGB_Image* dest,char* cmd)
{
	    int orig_height=src->height;
		int orig_width=src->width;
			    
	    int new_height=-1;
		int new_width=-1;
					    
		if(!strcmp(cmd,"scaleup")) // Case scaleup
		{
			new_width=2*orig_width;
			new_height=2*orig_height;
												        
			dest->height=new_height;
			dest->width=new_width;
			dest->max=src->max;
																			        
			dest->pixels=(RGBPixel**)malloc(sizeof(RGBPixel*)*new_height);
			for(int i=0;i<new_height;i++)
				dest->pixels[i]=(RGBPixel*)malloc(sizeof(RGBPixel)*new_width);
																							        
			for(int i=0;i<orig_height;i++)
			{
				for(int j=0;j<orig_width;j++)					
				{
					dest->pixels[2*i][2*j]=src->pixels[i][j];
					dest->pixels[2*i][2*j+1]=src->pixels[i][j];
					dest->pixels[2*i+1][2*j]=src->pixels[i][j];
					dest->pixels[2*i+1][2*j+1]=src->pixels[i][j];
				}
			}
			return 1;
		}

		if(!strcmp(cmd,"scaledown")) // Case scaledown
		{
			new_height=orig_height/2;
			new_width=orig_width/2;

			dest->height=new_height;
			dest->width=new_width;
			dest->max=src->max;						

			if(new_height<1 || new_width<1) // Case image become really small
			{
				printf("Error in Scaledown!\n");
				return 0;
			}
			else
				{
					dest->pixels=(RGBPixel**)malloc(sizeof(RGBPixel*)*new_height);
					for(int i=0;i<new_height;i++)
						dest->pixels[i]=(RGBPixel*)malloc(sizeof(RGBPixel)*new_width);
					//Memory Allocation

					for(int i=0;i<new_height;i++)
					{
						for(int j=0;j<new_width;j++)
						{
							dest->pixels[i][j].RGB[0]=((src->pixels[2*i][2*j].RGB[0])+(src->pixels[2*i+1][2*j].RGB[0])+(src->pixels[2*i][2*j+1].RGB[0])+(src->pixels[2*i+1][2*j+1].RGB[0]))/4;
																																																	            
							dest->pixels[i][j].RGB[1]=((src->pixels[2*i][2*j].RGB[1])+(src->pixels[2*i+1][2*j].RGB[1])+(src->pixels[2*i][2*j+1].RGB[1])+(src->pixels[2*i+1][2*j+1].RGB[1]))/4;
																																																				                
							dest->pixels[i][j].RGB[2]=((src->pixels[2*i][2*j].RGB[2])+(src->pixels[2*i+1][2*j].RGB[2])+(src->pixels[2*i][2*j+1].RGB[2])+(src->pixels[2*i+1][2*j+1].RGB[2]))/4;
						}
					}
					return 1;
				}
				//Pixel manipulation
		}
		return 0;
		// Return 1 when success
}

void grayScale(RGB_Image* src,Gray_Image* dst)
{
	dst->height=src->height;
	dst->width=src->width;
	dst->max=src->max;
				    
	int x=dst->height;
	int y=dst->width;

	dst->pixels=(GrayPixel**)malloc(sizeof(GrayPixel*)*x);
	for(int i=0;i<x;i++)
		dst->pixels[i]=(GrayPixel*)malloc(sizeof(GrayPixel)*y);
	//Memory Allocation

	for(int i=0;i<x;i++)
	{
		for(int j=0;j<y;j++)
		dst->pixels[i][j].Gray=(src->pixels[i][j].RGB[0])*0.299+(src->pixels[i][j].RGB[1])*0.587+(src->pixels[i][j].RGB[2])*0.114;
	} // GrayShift, with RGB.
}

int rotate(RGB_Image* src,RGB_Image* dst,char* cmd)
{
	int new_height=src->width;
	int new_width=src->height;
			    
	dst->height=new_height;
	dst->width=new_width;

	int cen_x=new_width/2;
	int cen_y=new_height/2;

	dst->pixels=(RGBPixel**)malloc(sizeof(RGBPixel*)*new_height);

	for(int j=0;j<new_height;j++)
		dst->pixels[j]=(RGBPixel*)malloc(sizeof(RGBPixel)*new_width);
	//Memory Allocation


	if(new_height%2!=0 && new_width%2!=0) // Case odd * odd image
	{	
		if(!strcmp(cmd,"left"))
			{
				for(int i=0;i<new_height;i++)
				{		
					for(int j=0;j<new_width;j++)
						dst->pixels[i][j]=src->pixels[j][2*cen_y-i];
				}
			}
		
		if(!strcmp(cmd,"right"))
			{
				for(int i=0;i<new_height;i++)
				{
					for(int j=0;j<new_width;j++)
						dst->pixels[i][j]=src->pixels[2*cen_x-j][i];
				}
			}

		return 1; 
	}

	if(new_height%2==0 && new_width%2==0) // Case even * even image OK
	{
		if(!strcmp(cmd,"left"))
		{
			for(int i=0;i<new_height;i++)
			{
				for(int j=0;j<new_width;j++)
					dst->pixels[i][j]=src->pixels[j][new_height-i-1];
			}
		}
		
		if(!strcmp(cmd,"right"))
		{
			for(int i=0;i<new_height;i++)
			{
				for(int j=0;j<new_width;j++)
					dst->pixels[i][j]=src->pixels[new_width-j-1][i];
			}

		}
		return 1; 
	}

	
	if(new_height%2!=0 && new_width%2==0) // Case odd * even image
	{
		if(!strcmp(cmd,"right"))
		{
			for(int i=0;i<new_height;i++)
			{
				for(int j=0;j<new_width;j++)
					dst->pixels[i][j]=src->pixels[new_width-1-j][i];
			}
		}

		if(!strcmp(cmd,"left")) 
		{
			for(int i=0;i<new_height;i++)
			{
				for(int j=0;j<new_width;j++)
					dst->pixels[i][j]=src->pixels[j][new_height-1-i];
			}
		}
		return 1;
	}

	if(new_height%2==0 && new_width%2!=0) // Case even * odd image OK
	{
		if(!strcmp(cmd,"left"))
		{
			for(int i=0;i<new_height;i++)
			{
				for(int j=0;j<new_width;j++)
					dst->pixels[i][j]=src->pixels[j][new_height-i-1];
			}
		}

		if(!strcmp(cmd,"right"))
		{
			for(int i=0;i<new_height;i++)
			{
				for(int j=0;j<new_width;j++)
					dst->pixels[i][j]=src->pixels[new_width-j-1][i];
			}
		}
		return 1;
	}
	return 0; // return 1 when it success
}





void colorSmooth(RGB_Image* src,RGB_Image* outsrc)
{
	    int height=src->height;
		int width=src->width;
		int max=src->max;

		outsrc->height=height;
		outsrc->width=width;
		outsrc->max=max;
	
		outsrc->pixels=(RGBPixel**)malloc(sizeof(RGBPixel*)*height);
		for(int i=0;i<height;i++)
			outsrc->pixels[i]=(RGBPixel*)malloc(sizeof(RGBPixel)*width);
		//Memory Allocation

		for(int i=1;i<height-1;i++)
		{
			for(int j=1;j<width-1;j++)
			{
				outsrc->pixels[i][j].RGB[0]=(src->pixels[i-1][j-1].RGB[0]+src->pixels[i-1][j].RGB[0]+src->pixels[i-1][j+1].RGB[0]+src->pixels[i][j-1].RGB[0]+src->pixels[i][j].RGB[0]+src->pixels[i][j+1].RGB[0]+src->pixels[i+1][j-1].RGB[0]+src->pixels[i+1][j].RGB[0]+src->pixels[i+1][j+1].RGB[0])/9;

				outsrc->pixels[i][j].RGB[1]=(src->pixels[i-1][j-1].RGB[1]+src->pixels[i-1][j].RGB[1]+src->pixels[i-1][j+1].RGB[1]+src->pixels[i][j-1].RGB[1]+src->pixels[i][j].RGB[1]+src->pixels[i][j+1].RGB[1]+src->pixels[i+1][j-1].RGB[1]+src->pixels[i+1][j].RGB[1]+src->pixels[i+1][j+1].RGB[1])/9;

				outsrc->pixels[i][j].RGB[2]=(src->pixels[i-1][j-1].RGB[2]+src->pixels[i-1][j].RGB[2]+src->pixels[i-1][j+1].RGB[2]+src->pixels[i][j-1].RGB[2]+src->pixels[i][j].RGB[2]+src->pixels[i][j+1].RGB[2]+src->pixels[i+1][j-1].RGB[2]+src->pixels[i+1][j].RGB[2]+src->pixels[i+1][j+1].RGB[2])/9;
			}
		} // Case : Inside.
								    
		for(int k=0;k<3;k++)
		{
			outsrc->pixels[0][0].RGB[k]=((src->pixels[0][1].RGB[k])+(src->pixels[1][0].RGB[k])+(src->pixels[1][1].RGB[k])+(src->pixels[0][0].RGB[k]))/4;
			// Case first apex

			outsrc->pixels[height-1][0].RGB[k]=((src->pixels[height-2][0].RGB[k])+(src->pixels[height-2][1].RGB[k])+(src->pixels[height-1][1].RGB[k])+(src->pixels[height-1][0].RGB[k]))/4;
			// Case second apex
														        
			outsrc->pixels[height-1][width-1].RGB[k]=((src->pixels[height-1][width-2].RGB[k])+(src->pixels[height-2][width-2].RGB[k])+(src->pixels[height-2][width-1].RGB[k])+(src->pixels[height-1][width-1].RGB[k]))/4;
			// case third apex
															        
			outsrc->pixels[0][width-1].RGB[k]=(src->pixels[1][width-1].RGB[k])+(src->pixels[0][width-2].RGB[k])+(src->pixels[1][width-2].RGB[k]+(src->pixels[0][width-1].RGB[k]))/4;
			// case fourth apex.
		} // Case : Apex

		for(int i=1;i<height-1;i++)
		{
			for(int k=0;k<3;k++) outsrc->pixels[i][0].RGB[k]=((src->pixels[i-1][0].RGB[k])+(src->pixels[i+1][0].RGB[k])+(src->pixels[i-1][1].RGB[k])+(src->pixels[i][1].RGB[k])+(src->pixels[i+1][1].RGB[k])+(src->pixels[i][0].RGB[k]))/6;
		} // left border
										    
		for(int j=1;j<width-1;j++)
		{
			for(int k=0;k<3;k++)
				outsrc->pixels[0][j].RGB[k]=(src->pixels[0][j-1].RGB[k]+src->pixels[0][j+1].RGB[k]+src->pixels[1][j].RGB[k]+src->pixels[1][j-1].RGB[k]+src->pixels[1][j+1].RGB[k]+src->pixels[0][j].RGB[k])/6;
		} // up border
											    
		for(int i=1;i<height-1;i++)
		{
			for(int k=0;k<3;k++)
				outsrc->pixels[i][width-1].RGB[k]=(src->pixels[i-1][width-1].RGB[k]+src->pixels[i+1][width-1].RGB[k]+src->pixels[i][width-2].RGB[k]+src->pixels[i-1][width-2].RGB[k]+src->pixels[i+1][width-2].RGB[k]+src->pixels[i][width-1].RGB[k])/6;
		} // right border
												    
		for(int j=1;j<width-1;j++)
		{
			for(int k=0;k<3;k++)
				outsrc->pixels[height-1][j].RGB[k]=(src->pixels[height-1][j-1].RGB[k]+src->pixels[height-1][j+1].RGB[k]+src->pixels[height-2][j-1].RGB[k]+src->pixels[height-2][j].RGB[k]+src->pixels[height-2][j+1].RGB[k]+src->pixels[height-1][j].RGB[k])/6;
		}// down border
}
