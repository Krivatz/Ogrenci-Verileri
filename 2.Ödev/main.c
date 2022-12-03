#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *fptr;
typedef struct ogrenci{
	
	char adi[50];
	char soyadi[50];
	char numarasi[25];
	float vize;
	float final;
	
	struct ogrenci *next;
	struct ogrenci *previous;
}dugum;




void yazma(dugum *head){
	fptr=fopen("ogrenci.txt","w");
	if(fptr==NULL){
		printf("dosya yok !");
		exit (0);
	}
	for(dugum *temp=head;temp!=NULL;temp=temp->next){
		fprintf(fptr,"\nAdi:%s\nSoyadi:%s\nNumarasi:%s\nVize Notu:%.1f\nFinal Notu:%.1f\n",temp->adi,temp->soyadi,temp->numarasi,temp->vize,temp->final);
	}
}





dugum *ekleme(dugum *head){
	system("cls");
	dugum *ogrenci=(dugum*)malloc(sizeof(dugum));
	printf("Kayit edilecek ogrencinin bilgilerini giriniz\n");
	printf("Ogrencinin adini giriniz:");
	scanf("%s",ogrenci->adi);
	printf("Ogrencinin soyadini giriniz:");
	scanf("%s",ogrenci->soyadi);
	printf("Ogrencinin numarasini giriniz:");
	scanf("%s",ogrenci->numarasi);
	printf("Ogrencinin vize notunu giriniz:");
	scanf("%f",&ogrenci->vize);
	printf("Ogrencinin final notunu giriniz:");
	scanf("%f",&ogrenci->final);
		if(head==NULL){
		head=ogrenci;
		head->previous=NULL;
		head->next=NULL;
		printf("%s numarali ogrenci basari ile kaydedildi.",ogrenci->numarasi);
	}
	else {
		ogrenci->next=head;
		head->previous=ogrenci;
		head=ogrenci;
		head->previous=NULL;
		printf("%s numarali ogrenci basari ile kaydedildi.",ogrenci->numarasi);
	}
	
	return head;
}




dugum *silme(dugum *head){
	system("cls");
	if(head=NULL){
		printf("kayıtli herhangi bir ogrenci yok!");
	}
	else{
		char num[20];
		printf("silinecek ogrencinin numarasini giriniz");
		scanf("%s",&num);
			if(head->next==NULL && (strcmp(head->numarasi, num)==0)){
				free(head);
				head=NULL;
				printf("Liste temizlendi");
			}
			else if(head->next!=NULL && (strcmp(head->numarasi, num)==0)){
				dugum *temp= head->next;
				free(head);
				head=temp;
				temp->previous=NULL;
				printf("%s numarali ogrenci listeden silindi",num);
			}
			else{
				dugum *temp=head;
				while(temp->next!=NULL){
					if(strcmp(temp->numarasi, num)==0){
						dugum *temp3=temp->next;
						dugum *temp2=temp->previous;
						free(temp);
						temp2->next=temp3;
						temp3->previous=temp2;
						printf("%s numarali ogrenci listeden silindi",num);
						
					}
					temp=temp->next;
				}
				if(strcmp(temp->numarasi, num)==0){
						dugum *temp3=temp->previous;
						free(temp);
						temp3->next=NULL;
						printf("%s numarali ogrenci listeden silindi",num);
						
				}
				
			}	
	}	
	return head;
}

dugum *listele(dugum *head){
	system("cls");
	if(head==NULL){
		printf("Liste bos!!!!!\n\n");
		
	}
	else{
		dugum *temp=head;
		
		printf("-----------------------Ogrenci Listesi--------------------------\n");
		while(temp!=NULL){
			printf("\n%s numarali ogrencinin \n adi: %s \n soyadi: %s \n vize notu:%.1f \n final notu:%.1f\n",temp->numarasi, temp->adi, temp->soyadi, temp->vize, temp->final );
			temp=temp->next;
		}
	}
	
	return 0;
}

void goster(struct ogrenci *i){
		printf("\n%s\n ",i->adi);
}


int main(){
	int menu;
	dugum *head=NULL;
	printf("UYARI! Bu uygulama bagli liste kullanmaktadir. Yaptiginiz girdilerin dosyaya kayit olmasini istiyorsaniz lutfen dogru cikis yapiniz!");
	while(1){
		printf("\nOgrenci kayit uygulamasi\n");
		printf("ogrenci kayidi icin 1\n");
		printf("var olan ogrenciyi silmek icin 2'e basin \n");
		printf("ogrenci listesini gormek icin 3'e basin \n");
		printf("dosyadan okuma icin 4\n");
		printf("cikis yapmak icin 0\n");
		scanf("%d",&menu);
		switch(menu){
			case 1:
				head=ekleme(head);
				yazma(head);
			break;
			
			case 2:
				head=silme(head);
			break;
			
			case 3:
				head=listele(head);
			break;
			
			case 4:
				fptr=fopen("ogrenci.txt","r");
				if(fptr==NULL){
				printf("dosya yok !");
				exit (0);
				}
				
				printf("Ogrenci listesi asagidaki gibidir. \n");
				while(!feof(fptr)){
				fread(&head,sizeof(struct ogrenci),1,fptr);
				goster(&head);
				}
	
				fclose(fptr);
				
			break;
			
			case 0:
				exit(0);
			break;
			
		 default:
				("hatali secim yaptiniz!!!! \n");
		}
	}
	return 0;
}