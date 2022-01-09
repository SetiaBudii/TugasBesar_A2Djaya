#include<stdio.h>
#include<windows.h>
#include<stdbool.h>
#include<time.h>
#include<stdlib.h>
#include<time.h>

/* Authors : A2Djaya
  
  Fardan Al Jihad			NIM:211524009
  Fariz Rahman Maulana		NIM:211524011
  Yayang Setia Budi			NIM:211524030
  versi: UI Minimalis 
  
*/

typedef struct{
	char nama[10];
	int score;
	int waktu;
}player;

typedef struct{
	char nama[10];
	int score;
	char ModeGame[10];
	char levelBot[10];
}highscore;

void koordinat(int x, int y);
void draw_papan(int x);
void settingGame();
char random_sos();
void level_easy();
void level_normal();
void level_hard();
void permainan_human(int z);
void permainan_bot(int z);
void cek_timer();
long detik_pertama();
void inputan_player();
void isi_papan();
void awal();
void input_nickname();
void ukuran_papan();
void levelGame();
bool cek_giliran();
void modeGame();
void cek_mode(int x);
bool cek_bariskolom(int baris,int kolom);
void tampil_giliran();
bool cek_isipetak(int x,int z);
void tampilan_skor();
void giveUP(char x);
char konversi_SOS(char z);
void cek_akhirGame();
void kalah(char arr[]);
void draw();
void menang(char nama[]);
bool cek_inputSOS(char huruf);
void pilihan_bot(int x,int y,char z);
void index_papan(int x);
void cek_sisawaktu(int timeP1,int timeP2);
void TampilWaktusisa();
void leader();
void Highscore();
void cek_skorBaris();
void cek_skorKolom();
void cek_skorDiagonalKiri();
void cek_skorDiagonalKanan();
void cekSkor();


//Daftar Variabel Global
player player1;
player player2;
char Petak[9][9];
int level;
int ukuranPapan;
int mode;
int giliran=2;
long detik_awal;
int totalBaris=0;
int totalKolom=0;
int totalDiagonalKanan=0;
int totalDiagonalKiri=0;

//Main program
int main(){
	awal();
	settingGame();
	cek_mode(mode);
	cek_akhirGame();
  
	return 0;
} 

//Modul pindah koordinat
void koordinat(int x, int y){
		HANDLE hConsoleOutput;
		COORD dwCursorPosition;
		dwCursorPosition.X = x;
		dwCursorPosition.Y = y;
		hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleCursorPosition(hConsoleOutput,dwCursorPosition);
}

//Modul Draw papan     								
void draw_papan(int x){
	
	int k,j,i;
	int nomor=1;
	x=x*3;
	
	system("cls");
	tampilan_skor();
	printf("\n\n\n");
	printf("\t\t   ");
	
	for(i=0;i<x;i++){				//untuk mencetak index nomor baris dan kolom kekanan
		printf("%d     ",nomor);
		nomor++;
	}
		
	nomor=1;
	printf("\n");
	
	for(k=0;k<x;k++){
		printf("\t\t");
		for(i=0;i<7*x-(x-1);i++){
			printf("=");
		}
		printf("\n");
		printf("\t       %d",nomor);
		printf("|");
		for(j=0;j<x;j++){
			printf("  %c  |",Petak[k][j]);
		}
		printf("\n");
		if(k==(x-1)){
			printf("\t\t");
			for(i=0;i<7*x-(x-1);i++){
				printf("=");
			}
		}
		nomor++;
	}
}    

//Modul Isi papan       							
void isi_papan(){
	int baris,kolom;
	
	for(baris=0;baris<9;baris++){
		for(kolom=0;kolom<9;kolom++){
			Petak[baris][kolom]=0;
		}
	}
}

//Modul Tampilan awal   							
void awal(){
	int i;
	char main;
	char awal[]="Selamat Datang di Game SOS by:A2Djaya";
	
	for(i=0;i<=79;i++){
		if(i<=strlen(awal)){
			koordinat(23+i,7);
			printf("%c",awal[i]);
		}
		koordinat(i,19);
		printf("%c",219);
		Sleep(10);
	}
	
	koordinat(28,17);
    printf("Press any key to continue...\n");
    getch();
}

//Modul Setting game								
void settingGame(){
	player1.score=0;
	player2.score=0;
	giliran=2;
	isi_papan();
	modeGame();
}

//Modul Memilih Game Mode							
void modeGame(){
	FILE *menu;
	char tulisan[150];
	
	do{
		system("cls");
		menu = fopen("Robot.txt", "rt");
		while((fgets(tulisan,150, menu))!= NULL){
			printf("\t%s", tulisan);
		}
	
		fclose(menu);
		koordinat(20,21);  printf(" Silakan pilih Mode permainan ");
		koordinat(19,23);  printf("[1] Vs.Human    [2] Vs.Computer ");
		koordinat(27,25); printf("Jawaban anda : ");
		koordinat(42,25); scanf("%d",&mode);
	}while(mode!=1 && mode!=2);
	
	
	if(mode==1){
		input_nickname();
	}else{
		levelGame();
	}	
}

//Modul	Input Nickname 								
void input_nickname(){
	system("cls");
	
	FILE *menu;
	char tulisan[150];
	
	menu = fopen("Robot.txt", "rt");
		while((fgets(tulisan,150, menu))!= NULL){
			printf("\t%s", tulisan);
		}
	
	fclose(menu);
	
	koordinat(20,21);
	printf("Masukan Nama P1 : "); scanf("%s", &player1.nama);
	
	if (mode == 1){
		getchar();
		koordinat(20,23);
		printf("Masukan Nama P2 : ");scanf("%s", &player2.nama);
	}else{
		if(level==1){
			strcpy(player2.nama,"FRIDAY");	
		}else if(level==2){
			strcpy(player2.nama,"EDITH");
		}else{
			strcpy(player2.nama,"JARVIS");
		}	
	}
	
	ukuran_papan();
}

//Modul	Memilih level game (untuk mode vs bot)		
void levelGame(){
	FILE *menu;
	char tulisan[150];
	
	do{
		system("cls");
		menu = fopen("Robot.txt", "rt");
		while((fgets(tulisan,150, menu))!= NULL){
			printf("\t%s", tulisan);
		}
	
		fclose(menu);
		koordinat(20,21);  printf(" Silakan pilih level permainan ");
		koordinat(19,23);  printf("[1] Easy  [2] Normal  [3] Hard ");
		koordinat(27,25); printf("Jawaban anda : ");
		koordinat(42,25); scanf("%d",&level);
	}while(level!=1 && level!=2 && level!=3);
	
	input_nickname();
}

//Modul Memilih Ukuran papan						
void ukuran_papan(){
	FILE *menu;
	char tulisan[150];
	
	do{
		system("cls");
		menu = fopen("Robot.txt", "rt");
		while((fgets(tulisan,150, menu))!= NULL){
			printf("\t%s", tulisan);
		}
	
		fclose(menu);
		koordinat(20,21);  printf(" Silakan ukuran papan permainan ");
		koordinat(19,23);  printf("   [1] 3x3   [2] 6x6   [3] 9x9  ");
		koordinat(27,25); printf("Jawaban anda : ");
		koordinat(42,25); scanf("%d",&ukuranPapan);
	}while(ukuranPapan!=1 && ukuranPapan!=2 && ukuranPapan!=3);
	
	if(ukuranPapan==1){
		player1.waktu=180;
		player2.waktu=180;
	}else if(ukuranPapan==2){
		player1.waktu=300;
		player2.waktu=300;
	}else{
		player1.waktu=600;
		player2.waktu=600;
	}
	
}

//Modul Input baris,kolom,SOS
void inputan_player(){
	int baris=0;
	int kolom=0;
	char sos=0;
	
	sini:
		
	draw_papan(ukuranPapan);
	detik_awal=detik_pertama();  //waktu awal saat input
	tampil_giliran();
	TampilWaktusisa();
	printf("\n\t\tMasukan SOS    : ");  scanf("%s",&sos);
	sos=konversi_SOS(sos);
	if(cek_inputSOS(sos)){
		system("cls");
		koordinat(22,7);
		printf("Masukkan antara S atau O !!!");
		getch();
		system("cls");
		goto sini;
	}
	giveUP(sos);
    printf("\t\tMasukan Baris  : ");  scanf("%d",&baris);
	printf("\t\tMasukan Kolom  : ");  scanf("%d",&kolom);
	if(cek_bariskolom(baris,kolom)){
		system("cls");
		koordinat(22,7);
		printf("Masukkan nomor hanya pada rentang 1 - %d!", 3*ukuranPapan);
		getch();
		system("cls");
		goto sini;
	}else if(cek_isipetak(baris,kolom)){
		system("cls");
		koordinat(22,7);
		printf("Petak ini sudah terisi pilih petak lain !!");
		getch();
		system("cls");
		goto sini;
	}
	cek_timer();
	Petak[baris-1][kolom-1]=sos;
	cekSkor();
	
}

//Modul Cek input SOS								
bool cek_inputSOS(char huruf){
	
	if (huruf!='S' &&  huruf!= 'O' && huruf!='n' && huruf!='N'){
		return 1;
	}
	else{
		return 0;
	}
}

//Modul Cek input petak								
bool cek_bariskolom(int baris,int kolom){
	if (baris < 1 || baris > 3*ukuranPapan || kolom < 1 || kolom > 3*ukuranPapan){
		return 1;
	}else {
		return 0;
	}
}

//modul cek isi petak apakah kosong atau tidak
bool cek_isipetak(int x,int z){
	if(Petak[x-1][z-1]!=0){
			return 1;
	}else{
		return 0;
	}
}

//modul konversi huruf ke Uppercase
char konversi_SOS(char z){
 if(z=='s'){
 	z='S';
  }else if(z=='o'){
  	z='O';	
  }else{
  	z=z;
  }
  
  return z;
}

//modul jika salah satu player menyerah
void giveUP(char x){
	if(x == 'N' || x == 'n'){
		if(cek_giliran()){
			player2.score=1000;
		}else{
			player1.score=1000;
		}
	cek_akhirGame();
	}
}
						
//Modul Cek giliran  				                 
bool cek_giliran(){
	if(giliran%2==0){
		return 1;
	}else{
		return 0;
	}
}
 
//Modul Cek mode permainan       					 
void cek_mode(int x){
	if(x==1){
		permainan_human(ukuranPapan);
	}else{
		permainan_bot(ukuranPapan);
	}
}

//Modul Permainan dengan Player						
void permainan_human(int z){
	int i;
	int hasil=(z*3)*(z*3);
	
	for(i=1;i<=hasil;i++){
		inputan_player();
		giliran++;	
	    cek_sisawaktu(player1.waktu,player2.waktu);	
	}
}

//Modul Permainan dengan Bot						
void permainan_bot(int z){
	int i;
	int hasil=(z*3)*(z*3);
	
	for(i=1;i<=hasil;i++){
		if(cek_giliran()){
			inputan_player();		
		}else{
			switch(level){
			 case 1:
				level_easy();
				break;
			 case 2:
				level_normal();
				break;
			 case 3:
			 	level_hard();
				break;		
			}
		}
		giliran++;	
	}
}

//Modul Cek Waktu 
void cek_timer(){
	long detik=time(NULL);
	
	if(cek_giliran()){
		player1.waktu=player1.waktu-(detik-detik_awal);	
	}else{
		player2.waktu=player2.waktu-(detik-detik_awal);
	}	
}

//modul untuk cek sisa waktu diakhir giliran,jika salah satu player waktunya habis maka untuk giliran kedepannya akan diskip
void cek_sisawaktu(int timeP1,int timeP2){
		if(timeP1<0 && timeP2>0){
			giliran=3;
		}else if(timeP2<0 && timeP1>0){
			giliran=4;
		}else if(timeP1<0 && timeP2<0){
			cek_akhirGame();
		}
	
}

//Modul Waktu awal giliran
long detik_pertama(){
	time_t detik;
	detik=time(NULL);
	return detik;
}

//Modul menampilkan sisa waktu
void TampilWaktusisa(){
	if(mode==1){
		if(cek_giliran()){
			printf("\n\t\tSisa waktu     : %d menit %d detik",player1.waktu/60,player1.waktu-(60*(player1.waktu/60)));
			printf("\n\n\t\t_______________\n\n");
		}else{
			printf("\n\t\tSisa waktu     : %d menit %d detik",player2.waktu/60,player2.waktu-(60*(player2.waktu/60)));
			printf("\n\n\t\t_______________\n\n");
		}
	}
}

//modul menampilkan giliran player
void tampil_giliran(){
	printf("\n\n");
	if(cek_giliran()){
		printf("\t\tGiliran        : %s\n",player1.nama);		
	}else{
		printf("\t\tGiliran        : %s\n",player2.nama);
	}
}

//modul untuk menampilkan skor 
void tampilan_skor(){
			int z;
			int sisadetik2,sisadetik1,sisamenit1,sisamenit2;
			
			if(ukuranPapan==1){
				z=19;
			}else if(ukuranPapan==2){
				z=10;
			}else{
				z=0;
			}
		  	koordinat(37-z,3);
			printf("%c%c%c%c%c%c%c %c%c%c%c%c%c%c",218,196,196,196,196,196,191,218,196,196,196,196,196,191);
			koordinat(26-z,4);
			printf("%c%c%c%c%c%c%c%c%c%c%c%c     %c %c     %c%c%c%c%c%c%c%c%c%c%c%c",218,196,196,196,196,196,196,196,196,196,196,180,179,179,195,196,196,196,196,196,196,196,196,196,196,191);
			koordinat(26-z,5);
			printf("%c          %c     %c %c     %c          %c",179,179,179,179,179,179);
			koordinat(40-z,5);
			printf("%d",player1.score);
			koordinat(48-z,5);
			printf("%d",player2.score);
			koordinat(28-z,5);
			printf("%s",player1.nama);
			koordinat(53-z,5);
			printf("%s",player2.nama);
			koordinat(26-z,6);
			printf("%c%c%c%c%c%c%c%c%c%c%c%c     %c %c     %c%c%c%c%c%c%c%c%c%c%c%c",192,196,196,196,196,196,196,196,196,196,196,180,179,179,195,196,196,196,196,196,196,196,196,196,196,217);
			koordinat(37-z,7);
			printf("%c%c%c%c%c%c%c %c%c%c%c%c%c%c",192,196,196,196,196,196,217,192,196,196,196,196,196,217);
			if(mode==1){
			  sisadetik2=player2.waktu-(60*(player2.waktu/60));
			  sisamenit2=player2.waktu/60;
			  sisadetik1=player1.waktu-(60*(player1.waktu/60));
			  sisamenit1=player1.waktu/60;	
			if(player1.waktu<0){
				koordinat(37-z,8);
				printf(" Habis");
			}else if(sisadetik1<10){
				koordinat(37-z,8);
				printf(" 0%d:0%d",sisamenit1,sisadetik1); 
			}else{
				koordinat(37-z,8);
				printf(" 0%d:%d",sisamenit1,sisadetik1);
			}
			
			if(player2.waktu<0){
				koordinat(45-z,8);
				printf(" Habis");
			}else if(sisadetik2<10){
				koordinat(45-z,8);
				printf(" 0%d:0%d",sisamenit2,sisadetik2); 
			}else{
				koordinat(45-z,8);
				printf(" 0%d:%d",sisamenit2,sisadetik2);
			}			
	}
}

//Modul Random SOS
char random_sos(){
	char huruf;
	int angka;
	
	srand(time(NULL));
	angka=rand()%2;
	
	if(angka==1){
		huruf='S';
	}else{
		huruf='O';
	}
	
	return huruf;
}

//Modul Pergerakan Bot easy							
void level_easy(){
	int baris,kolom,k,j;
	char sos=0;
	
	draw_papan(ukuranPapan);
	for(k=0;k<ukuranPapan*3;k++){
		for(j=0;j<ukuranPapan*3;j++){
			if(Petak[k][j]== 0 ){
				sos=random_sos();
				baris=k;
				kolom=j;
				break;
			}
		}
		if(sos!=0){
			break;
		}
	}
	
	Petak[k][j]=sos;
	cekSkor();
	pilihan_bot(baris,kolom,sos);	
}
	
//Modul	Pergerakan Bot normal						
void level_normal(){
	
	draw_papan(ukuranPapan);
	
	int batas=ukuranPapan*3;
	srand(time(NULL));
	int baris;
	int kolom;
	char sos;
	
	
	while(1){
		baris=rand()%batas;
		kolom=rand()%batas;
		
		if(Petak[baris][kolom]==0){
			sos=random_sos();
			break;
		}
	}
	
	Petak[baris][kolom]=sos;
	cekSkor();
	pilihan_bot(baris,kolom,sos);
}

//modul bot level hard
void level_hard(){
	
	draw_papan(ukuranPapan);
	int baris,kolom,i,j;
	char k;
	for (baris = 0; baris < 3*ukuranPapan; baris++){
		for (kolom = 0; kolom < 3*ukuranPapan; kolom++){
		if (Petak[baris][kolom] == 'S'){
				// Vertikal atau Horizontal SO
				if (Petak[baris-1][kolom] == 'O' && Petak[baris-2][kolom] == 0 && baris - 2 >= 0){								
					Petak[baris-2][kolom] = 'S';
					i = baris - 2;
					j = kolom;
					k = 'S';
					cekSkor();
					pilihan_bot(i, j, k);
					return;
				}
				if (Petak[baris][kolom+1] == 'O' && Petak[baris][kolom+2] == 0 && kolom + 2 < 3*ukuranPapan){
					Petak[baris][kolom+2] = 'S';
					i = baris;
					j = kolom + 2;
					k = 'S';
					cekSkor();
					pilihan_bot(i, j, k);
					return;
				}
				if (Petak[baris+1][kolom] == 'O' && Petak[baris+2][kolom] == 0 && baris + 2 < 3*ukuranPapan){
					Petak[baris+2][kolom] = 'S';
					i = baris + 2;
					j = kolom;
					k = 'S';
					cekSkor();
					pilihan_bot(i, j, k);
					return;
				}
				if (Petak[baris][kolom-1] == 'O' && Petak[baris][kolom-2] == 0 && kolom - 2 >= 0){
					Petak[baris][kolom-2] = 'S';
					i = baris;
					j = kolom - 2;
					k = 'S';
					cekSkor();
					pilihan_bot(i, j, k);
					return;
				}
				// Computer mencari 'SO...' berurutan (diagonal)
				if (Petak[baris-1][kolom+1] == 'O' && Petak[baris-2][kolom+2] == 0 && baris-2 >= 0 && kolom + 2 < 3*ukuranPapan){		
					Petak[baris-2][kolom+2] = 'S';
					i = baris - 2;
					j = kolom + 2;
					k = 'S';
					cekSkor();
					pilihan_bot(i, j, k);
					return;
				}
				if (Petak[baris+1][kolom+1] == 'O' && Petak[baris+2][kolom+2] == 0 && baris + 2 < 3*ukuranPapan && kolom + 2 < 3*ukuranPapan){
					Petak[baris+2][kolom+2] = 'S';
					i = baris + 2;
					j = kolom + 2;
					k = 'S';
					cekSkor();
					pilihan_bot(i, j, k);
					return;
				}
				if (Petak[baris+1][kolom-1] == 'O' && Petak[baris+2][kolom-2] == 0 && baris + 2 < 3*ukuranPapan && kolom - 2 >= 0){
					Petak[baris+2][kolom-2] = 'S';
					i = baris + 2;
					j = kolom - 2;
					k = 'S';
					cekSkor();
					pilihan_bot(i, j, k);
					return;
				}
				if (Petak[baris-1][kolom-1] == 'O' && Petak[baris-2][kolom-2] == 0 && baris - 2 >= 0 && kolom - 2 >= 0){
					Petak[baris-2][kolom-2] = 'S';
					i = baris - 2;
					j = kolom - 2;
					k = 'S';
					cekSkor();
					pilihan_bot(i, j, k);
					return;
				}
				// Computer mencari 'S...S' berurutan (horizontal atau vertikal)
				if (Petak[baris+2][kolom] == 'S' && Petak[baris+1][kolom] == 0 && baris + 1 < 3*ukuranPapan){
					Petak[baris+1][kolom] = 'O';
					i = baris + 1;
					j = kolom;
					k = 'O';
					cekSkor();
					pilihan_bot(i, j, k);
					return;
				}
				if (Petak[baris][kolom+2] == 'S' && Petak[baris][kolom+1] == 0 && kolom + 2 < 3*ukuranPapan){
					Petak[baris][kolom+1] = 'O';
					i = baris;
					j = kolom + 1;
					k = 'O';
					cekSkor();
					pilihan_bot(i, j, k);
					return;
				}
				if (Petak[baris-2][kolom] == 'S' && Petak[baris-1][kolom] == 0 && baris - 1 >= 0){
					Petak[baris-1][kolom] = 'O';
					i = baris - 1;
					j = kolom;
					k = 'O';
					cekSkor();
					pilihan_bot(i, j, k);
					return;
				}
				if (Petak[baris][kolom-2] == 'S' && Petak[baris][kolom-1] == 0 && kolom - 2 >= 0){
					Petak[baris][kolom-1] = 'O';
					i = baris;
					j = kolom - 1;
					k = 'O';
					cekSkor();
					pilihan_bot(i, j, k);
					return;
				}
				// Computer mencari 'S...S' berurutan (diagonal)
				if (Petak[baris-2][kolom+2] == 'S' && Petak[baris-1][kolom+1] == 0 && baris - 1 >= 0 && kolom + 1 < 3*ukuranPapan){		
					Petak[baris-1][kolom+1] = 'O';
					i = baris - 1;
					j = kolom + 1;
					k = 'O';
					cekSkor();
					pilihan_bot(i, j, k);
					return;
				}
				if (Petak[baris+2][kolom+1] == 'S' && Petak[baris+1][kolom+1] == 0 && baris + 1 < 3*ukuranPapan && kolom + 1 < 3*ukuranPapan){
					Petak[baris+1][kolom+1] = 'O';
					i = baris + 1;
					j = kolom + 1;
					k = 'O';
					cekSkor();
					pilihan_bot(i, j, k);
					return;
				}
				if (Petak[baris+2][kolom-2] == 'S' && Petak[baris+1][kolom-1] == 0 && baris + 1 < 3*ukuranPapan && kolom - 1 >= 0){
					Petak[baris+1][kolom-1] = 'O';
					i = baris + 1;
					j = kolom - 1;
					k = 'O';
					cekSkor();
					pilihan_bot(i, j, k);
					return;
				}
				if (Petak[baris-2][kolom-2] == 'S' && Petak[baris-1][kolom-1] == 0 && baris - 1 >= 0 && kolom - 1 >= 0){
					Petak[baris-1][kolom-1] = 'O';
					i = baris - 1;
					j = kolom - 1;
					k = 'O';
					cekSkor();
					pilihan_bot(i, j, k);
					return;
				}
			}
		}
	}
	level_normal();	
}

//modul menampilkan pilihan bot
void pilihan_bot(int x,int y,char z){
	x=x+1;
	y=y+1;
	system("cls");
	koordinat(22,7);
	printf("Komputer memilih baris %d, kolom %d, huruf %c",x,y,z);
	getch();
}

//Modul Cek Skor per Baris
void cek_skorBaris(){
	int totalskor;
	int i,j;
	int total=0;
	
	for(i=0;i<3*ukuranPapan;i++){
		for(j=0;j<3*ukuranPapan-2;j++){
			if(Petak[i][j]=='S' && Petak[i][j+1]=='O' && Petak[i][j+2]=='S'){
				total++;
			}
		}
	}
	
	totalskor=total-totalBaris;
	totalBaris=total;
	
	if(cek_giliran()){
		player1.score=player1.score+totalskor;
	}else{
		player2.score=player2.score+totalskor;
	}
	
}

//Modul Cek Skor per kolom
void cek_skorKolom(){
	int totalskor;
	int i,j;
	int total=0;
	
	for(i=0;i<3*ukuranPapan-2;i++){
		for(j=0;j<3*ukuranPapan;j++){
			if(Petak[i][j]=='S' && Petak[i+1][j]=='O' && Petak[i+2][j]=='S'){
				total++;
			}
		}
	}
	
	
	totalskor=total-totalKolom;
	totalKolom=total;
	
	if(cek_giliran()){
		player1.score=player1.score+totalskor;
	}else{
		player2.score=player2.score+totalskor;
	}
	
}

//Modul Cek Skor per diaognal kearah kanan
void cek_skorDiagonalKanan(){
	int totalskor;
	int i,j;
	int total=0;
	
	for(i=0;i<3*ukuranPapan-2;i++){
		for(j=0;j<3*ukuranPapan;j++){
			if(Petak[i][j]=='S' && Petak[i+1][j+1]=='O' && Petak[i+2][j+2]=='S'){
				total++;
			}
		}
	}
	
	
	totalskor=total-totalDiagonalKanan;
	totalDiagonalKanan=total;
	
	if(cek_giliran()){
		player1.score=player1.score+totalskor;
	}else{
		player2.score=player2.score+totalskor;
	}
	
}

//Modul Cek Skor per diaognal kearah kiri
void cek_skorDiagonalKiri(){
	int totalskor;
	int i,j;
	int total=0;
	
	for(i=0;i<3*ukuranPapan-2;i++){
		for(j=3*ukuranPapan-1;j>1;j--){
			if(Petak[i][j]=='S' && Petak[i+1][j-1]=='O' && Petak[i+2][j-2]=='S'){
				total++;
			}
		}
	}
	
	
	totalskor=total-totalDiagonalKiri;
	totalDiagonalKiri=total;
	
	if(cek_giliran()){
		player1.score=player1.score+totalskor;
	}else{
		player2.score=player2.score+totalskor;
	}
	
}

//Modul untuk cek Skor terkini
void cekSkor(){
	int temp=player1.score+player2.score;
	cek_skorBaris();
	cek_skorKolom();
	cek_skorDiagonalKanan();
	cek_skorDiagonalKiri();
	
	if(temp<(player1.score+player2.score)){
		giliran++;
	}
}

//Modul untuk menentukan draw/kalah/menang
void cek_akhirGame(){
	
	if(player1.score>player2.score){
		menang(player1.nama);
		if(player1.score<1000){
			system("cls");
			Highscore();
			leader();
		}
	}else if(player1.score<player2.score && mode==1){
		menang(player2.nama);
		if(player2.score<1000){
			system("cls");
			Highscore();
			leader();
		}
	}else if(player1.score==player2.score){
		draw();
	}else if(player1.score<player2.score && mode==2){
		kalah(player1.nama);
	}
	
	exit(0);
}	

//Modul jika game berkahir dengan kemenangan salah satu player
void menang(char nama[]){
		system("cls");
		int i,j;
		char menang[100];
		strcpy(menang,"Selamat ");
		strcat(menang,nama);
		strcat(menang,", anda telah memenangkan permainan ini. Nice Game!!!  ");

		for(i=3;i<=5;i+=2){
			for(j=0;j<strlen(menang)+10;j++){
				koordinat(j,i);
				printf("%c",196);
				Sleep(10);
			}	
		}

		koordinat(7,4);
		for(i=0;i<strlen(menang);i++){
			printf("%c",menang[i]);
			Sleep(100);
		}
		
		printf("\n\n\n\n\n\n\n\t\t\tPress any key to exit....\n\n\n");
getch();
}

//Modul jika Game berakhir Draw
void draw(){
		system("cls");
		int i,j;
		char imbang[]="Tampaknya kita tidak mendapatkan pemenang Game Draw!!";

		for(i=3;i<=5;i+=2){
			for(j=0;j<strlen(imbang)+10;j++){
				koordinat(j,i);
				printf("%c",196);
				Sleep(10);
			}
		}

		koordinat(7,4);
		for(i=0;i<strlen(imbang);i++){
			printf("%c",imbang[i]);
			Sleep(100);
		}
		
		printf("\n\n\n\n\n\n\n\t\t\tPress any key to exit....\n\n\n");
}

//Modul jika game berkahir player kalah dari bot
void kalah(char arr[]){
	system("cls");
	int i,j;
	char kalah[100];
	strcpy(kalah,"Oppsss ");
	strcat(kalah,arr);
	strcat(kalah,", Tampaknya anda kalah dari Bot kali ini, tetap semangat!!!");

	for(i=3;i<=5;i+=2){
		for(j=0;j<strlen(kalah)+10;j++){
			koordinat(j,i);
			printf("%c",196);
			Sleep(10);
		}
	}	

	koordinat(7,4);
	for(i=0;i<strlen(kalah);i++){
		printf("%c",kalah[i]);
		Sleep(100);
	}
	
	printf("\n\n\n\n\n\n\n\t\t\tPress any key to exit....\n\n\n");
}

//Modul memasukan HighScore kedalam file Skor.txt
void Highscore(){ 
    player user;
    FILE *score;
    if ((score = fopen("Skor.txt", "ab+")) == NULL)
	{
		printf ("File tidak dapat dibuka\n");
		exit(1);
	}
	
	if(player1.score<player2.score){
		strcpy(user.nama,player2.nama);
		user.score=player2.score;
	}else if(player1.score>player2.score){
		strcpy(user.nama,player1.nama);
		user.score=player1.score;
	}
    fwrite(&user, sizeof(user), 1, score);
    fclose(score);
}

//Modul untuk menampilkan Highscore
void leader(){ 
    player user;
    FILE *score;
	score=fopen("Skor.txt", "rb+");
	printf("\t\t\n Leader Board \n");
	while(fread(&user, sizeof(user), 1, score)){
    	printf("%s\t%d\n",user.nama,user.score);
	}
	fclose(score);
}



