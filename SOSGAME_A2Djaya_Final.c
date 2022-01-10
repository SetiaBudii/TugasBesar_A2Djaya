#include<stdio.h>
#include<windows.h>
#include<stdbool.h>
#include<time.h>
#include<stdlib.h>
#include<time.h>

#define reset 7

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
	char ModeGame[14];
	char levelBot[14];
	char papan[5];
}highscore;

//----------------------Modul Tampilan  dan settingan tertentu---------------------------//
void menu();
void draw_papan(int x);
void settingGame();
void awal();
void isi_papan();
void input_nickname();
void ukuran_papan();
void levelGame();
void tampil_giliran();
void tampilan_skor();
void kalah(char arr[]);
void draw();
void menang(char nama[]);
void TampilWaktusisa();
void leader();
void Highscore();
void setwarna(unsigned short color);
void koordinat(int x, int y);
void kotak();
void aboutUs();
void aturanMain(); 
void header();
void sort(highscore data);



//----------------------Modul Jalannya permainan vs bot maupun vs player---------------------------//
char random_sos();
void level_easy();
void level_normal();
void level_hard();
void permainan_human(int z);
void permainan_bot(int z);
void inputan_player();

//----------------------Modul Cek kondisi tertentu dalam permainan---------------------------//
void cek_timer();
long detik_pertama();
bool cek_giliran();
void modeGame();
void cek_mode(int x);
bool cek_bariskolom(int baris,int kolom);
bool cek_isipetak(int x,int z);
void giveUP(char x);
char konversi_SOS(char z);
void cek_akhirGame();
bool cek_inputSOS(char huruf);
void pilihan_bot(int x,int y,char z);
void cek_sisawaktu(int timeP1,int timeP2);
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
	menu();
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

//Modul menu awal
void menu(){
	int pilihan;
	int acak;
	int i;
	
	printf("\n\n");
	FILE *menu;
	char tulisan[150];
	
	do{
		system("cls");
		menu = fopen("tampilanawal.txt", "rt");
		while((fgets(tulisan,150, menu))!= NULL){
			srand(time(NULL)+i);
			acak=(rand()%3+1)+9;
			setwarna(acak);
			printf("\t%s", tulisan);
			i++;
		}
	
		fclose(menu);
		setwarna(reset);
		printf("\n\n\n\t  [1] Main   [2] Highscore   [3] Aturan Main   [4] About Us   [5] Exit");
		printf("\n\n\n\t\t\t\t      Jawaban Anda : "); scanf("%d",&pilihan);
	}while(pilihan<1 || pilihan>5);
	
	
	if(pilihan==1){
		awal();
	}else if(pilihan==2){
		leader();
	}else if(pilihan==3){
		aturanMain(); 
	}else if(pilihan==4){
		aboutUs();
	}else if(pilihan==5){
		exit(1);
	}
}

//Modul menampilkan nama pembuat program
void aboutUs(){
	FILE *about;
	char tulisan[150];
	system("cls");
		about = fopen("aboutus.txt", "rt");
		while((fgets(tulisan,150, about))!= NULL){
			printf("\t%s", tulisan);
		}
	
		fclose(about);
		getch();
		
		menu();
}

//Modul untuk menampilkan aturan permainan
void aturanMain(){
	FILE *aturan;
	char tulisan[150];
	system("cls");
		aturan = fopen("Aturan_Main.txt", "rt");
		while((fgets(tulisan,150, aturan))!= NULL){
			printf("\t%s", tulisan);
		}
	
		fclose(aturan);
		getch();
		
		menu();
}

//Modul Header (tampilan diatas papan pemilihan)
void header(){
	printf("\n\n\n\n\n\n\n\n");
	printf("\t    2       749         277777      74      7     28     97    7\n");
	printf("\t    88     577888       88   788    88     88     788   44     88\n");
	printf("\t   7 87        88       88     88   58    7 88      88 7      7 88\n");
	printf("\t  27 88        87       88      88  48    8  84      88       0 78\n");
	printf("\t  877 88      8         88      88  58   727 08      28      077 88\n");
	printf("\t 2     8    77          88     88   58   2    88     48     77    80 \n");
	printf("\t48     88  8888884      88777482    88  88    484    88    787    887\n");
	printf("\t                                 97785                               \n");
}

//Modul Draw papan     								
void draw_papan(int x){
	system("cls");
	int i,j,k;
	int baris=0;
	int kolom=0;
	int nomor=1;
	
	switch(x){
		case 1:
			k=4;
			break;
		case 2:
			k=2;
			break;
		case 3:
			k=0;
			break;		
	}
	
	tampilan_skor();
	
	//tabel kebawah
	for(i=0;i<=3*x;i++){
		for(j=0;j<12*x;j++){
			koordinat(13+k+(6*i),10+j);
			printf("%c",186);
			
		}
	}
	
	//tabel kekanan
	for(i=0;i<x*3+1;i++){
			for(j=0;j<7*(x*3)-(x*3)+1;j++){
				koordinat(13+k+j,10+(4*i));
				printf("=");
			}
	}
	
	//normor
	for(i=0;i<x*3;i++){
		for(j=0;j<x*3;j++){
			koordinat(14+k+(6*j),11+(4*i));
			printf("%d",nomor);
			nomor++;
		}
	}
	
	//isi papan	
	for(i=0;i<x*3;i++){
		for(j=0;j<x*3;j++){
			koordinat(16+k+(6*j),12+(4*i));
			setwarna(10);
			printf("%c",Petak[i][j]);
		}
	}setwarna(reset);
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
	
	system("cls");
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

	
	do{
		system("cls");
		header();
		kotak();
		koordinat(24,21);  printf(" Silakan pilih Mode permainan ");
		koordinat(23,23);  printf("[1] Vs.Human    [2] Vs.Computer ");
		koordinat(31,25); printf("Jawaban anda : ");
		koordinat(46,25); scanf("%d",&mode);
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
	header();
	kotak();
	koordinat(24,21);
	getchar();
	printf("Masukan Nama P1 : "); scanf("%[^\n]s", &player1.nama);
	
	if (mode == 1){
		koordinat(24,23);
		getchar();
		printf("Masukan Nama P2 : ");scanf("%[^\n]s", &player2.nama);
	}else{
		if(level==1){
			strcpy(player2.nama,"EDITH");	
		}else if(level==2){
			strcpy(player2.nama,"JARVIS");
		}else{
			strcpy(player2.nama,"ULTRON");
		}	
	}
	
	ukuran_papan();
}

//Modul	Memilih level game (untuk mode vs bot)		
void levelGame(){
	
	do{
		system("cls");
		header();
		kotak();
		koordinat(24,21);  printf(" Silakan pilih level permainan ");
		koordinat(23,23);  printf("[1] Easy  [2] Normal  [3] Hard ");
		koordinat(31,25); printf("Jawaban anda : ");
		koordinat(46,25); scanf("%d",&level);
	}while(level!=1 && level!=2 && level!=3);
	
	input_nickname();
}

//Modul Memilih Ukuran papan						
void ukuran_papan(){
	
	do{
		system("cls");
		header();
		kotak();
		koordinat(24,21);  printf(" Silakan ukuran papan permainan ");
		koordinat(23,23);  printf("   [1] 3x3   [2] 6x6   [3] 9x9  ");
		koordinat(31,25); printf("Jawaban anda : ");
		koordinat(46,25); scanf("%d",&ukuranPapan);
	}while(ukuranPapan!=1 && ukuranPapan!=2 && ukuranPapan!=3);
	
	if(ukuranPapan==1){
		player1.waktu=180;
		player2.waktu=180;
	}else if(ukuranPapan==2){
		player1.waktu=300;
		player2.waktu=300;
	}else{
		player1.waktu=540;
		player2.waktu=540;
	}
	
}

//Modul Input baris,kolom,SOS
void inputan_player(){
	int baris=0;
	int kolom=0;
	char sos=0;
	int barkol;
	
	
	detik_awal=detik_pertama();  //waktu awal saat input
	sini:
	fflush(stdin);
	draw_papan(ukuranPapan);
	printf("\n");
	tampil_giliran();
	TampilWaktusisa();
	printf("\n\t\t Masukan SOS    : ");  scanf("%s",&sos);
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
    printf("\n\t\t Masukan Petak  : ");  scanf("%d",&barkol);
    baris = (barkol-1)/(ukuranPapan*3);
	kolom = (barkol-1)%(ukuranPapan*3);
	if(cek_bariskolom(baris,kolom)){
		system("cls");
		koordinat(22,7);
		printf("Masukkan nomor hanya pada rentang 1 - %d!", (3*ukuranPapan)*(3*ukuranPapan));
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
	Petak[baris][kolom]=sos;
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
	if ((baris >= 0 && baris < 3*ukuranPapan) && (kolom >=0 && kolom < 3*ukuranPapan)){
		return 0;
	}else {
		return 1;
	}
}

//modul cek isi petak apakah kosong atau tidak
bool cek_isipetak(int x,int z){
	if(Petak[x][z]!=0){
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
			printf("\n\t\t Sisa waktu     : %d menit %d detik",player1.waktu/60,player1.waktu-(60*(player1.waktu/60)));
			printf("\n\n\t\t _______________\n\n");
		}else{
			printf("\n\t\t Sisa waktu     : %d menit %d detik",player2.waktu/60,player2.waktu-(60*(player2.waktu/60)));
			printf("\n\n\t\t _______________\n\n");
		}
	}
}

//modul menampilkan giliran player
void tampil_giliran(){
	printf("\n\n\n\n");
	if(cek_giliran()){
		printf("\t         Giliran        : %s\n",player1.nama);		
	}else{
		printf("\t         Giliran        : %s\n",player2.nama);
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
				z=4;
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
	int hasil;
	
	hasil=((x*ukuranPapan*3)+y)+1;
	system("cls");
	koordinat(22,7);
	printf("Komputer memilih Petak %d, huruf %c",hasil,z);
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
		}
	}else if(player1.score<player2.score && mode==1){
		menang(player2.nama);
		if(player2.score<1000){
			system("cls");
			Highscore();
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
			Sleep(40);
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
    highscore user;
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
	
	if(ukuranPapan==1){
		strcpy(user.papan,"3x3");
	}else if(ukuranPapan==2){
		strcpy(user.papan,"6x6");
	}else{
		strcpy(user.papan,"9x9");
	}
	
	if(mode==1){
		strcpy(user.ModeGame,"Multiplayer  ");
		strcpy(user.levelBot,"   -----  ");
	}else{
		strcpy(user.ModeGame,"Single Player");
		if(level==1){
			strcpy(user.levelBot,"    Easy  ");
		}else if(level==2){
			strcpy(user.levelBot,"    Normal");
		}else{
			strcpy(user.levelBot,"    Hard  ");
		}
    }
    fwrite(&user, sizeof(user), 1, score);
    fclose(score);
    

    sort(user);
}

//Modul untuk menampilkan Highscore
void leader(){ 
	system("cls");
	int i=3;
	int j=6;
    highscore user;
    FILE *score;
	score=fopen("Skor.txt", "rb+");
	printf("\n\t\t\t\t Leader Board \n\n\n");
	printf("   Nama           Skor             Mode                   Level       Ukuran Papan\n\n\n");
	while(fread(&user, sizeof(user), 1, score)){
		koordinat(i,j); printf("%s",user.nama);
		i+=16;
		koordinat(i,j); printf("%d",user.score);
		i+=13;
		koordinat(i,j); printf("%s",user.ModeGame);
		i+=23;
		koordinat(i,j); printf("%s",user.levelBot);
		i+=19;
		koordinat(i,j); printf("%s",user.papan);
		i=3;
		j++;
	}
	fclose(score);
	
	getch();
	menu();
}

// Modul mengganti warna text dan lainnya									( By : Yayang Setia Budi )
void setwarna(unsigned short color){
    HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hCon,color);
}

void kotak(){
	int i,j;
	
	for(i=0;i<=1;i++){
			for(j=0;j<43;j++){
				koordinat(17+j,18+(10*i));
				printf("=");
			}
	}
	
	for(i=0;i<2;i++){
		for(j=1;j<=9;j++){
			koordinat(17+(42*i),18+j);
			printf("%c",186);
			
		}
	}
}

//Modul untuk sorting leaderboard
void sort(highscore data){
	player penampung[20];
	int count = 0;
	int i,j,temp;
	char tmpname[10];
	
	FILE *dataAsli;
	FILE *datapenampung;
	dataAsli = fopen("Skor.txt","rb");
	datapenampung = fopen("Temp_Skor.txt","wb");
	while (fread(&data, sizeof(data),1,dataAsli)){
		penampung[count].score = data.score;
		strcpy(penampung[count].nama,data.nama);
		count++;
	}
	
	for (i = 0; i<count-1;i++){
		for (j = i + 1; j<count; j++){
			if (penampung[i].score<=penampung[j].score){
				temp = penampung[i].score;
				penampung[i].score= penampung[j].score;
				penampung[j].score= temp;
				
				strcpy(tmpname,penampung[i].nama);
				strcpy(penampung[i].nama,penampung[j].nama);
				strcpy(penampung[j].nama,tmpname);
			}
		}
	}
	
	if(count!=1){
		for (i = 0; i<count; i++){
				rewind(dataAsli);
				while (fread(&data, sizeof(data),1,dataAsli)){
					if (penampung[i].score==data.score && strcmp(penampung[i].nama,data.nama)==0 ){
						fwrite(&data, sizeof(data),1,datapenampung);
					}
				}
		}
			fclose(dataAsli);
		  	fclose(datapenampung);
		  		dataAsli = fopen("Skor.txt","wb");
		  		datapenampung = fopen("Temp_Skor.txt","rb");
		  		while (fread(&data,sizeof(data),1, datapenampung)){
		  			fwrite(&data,sizeof(data),1,dataAsli);
				  }
				fclose(dataAsli);
				fclose(datapenampung);
	}
	
}
