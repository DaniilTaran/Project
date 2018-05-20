#include <SFML/Graphics.hpp>
#include <fstream>
#pragma warning(disable : 4996)
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
using namespace std;
using namespace sf;

//Функция выбора случайного слова
char ViborSlova(char slovo[20])
{
	int row = 1;

	srand(time(NULL));
	int rowNumber = 1 + rand() % 260;

	ifstream file("words/Слова.txt");

	while (!file.eof())
	{
		file.getline(slovo, 20);
		if (rowNumber == row)
		{
			break;
		}
		row++;
	}
	return 0;
}

//Функция окна меню
void menu(RenderWindow & window)
{

	Texture aboutTexture, menutexture;
	aboutTexture.loadFromFile("images/about.png");
	menutexture.loadFromFile("images/3ФОН.png");

	Font font1, font2, font3;
	font1.loadFromFile("font/10460.ttf");
	font2.loadFromFile("font/11814.ttf");
	font3.loadFromFile("font/yugothiclight.ttf");

	Text text1, text2, text3;

	text1.setFont(font3);
	text1.setString(L"Новая игра");
	text1.setPosition(320, 280);
	text1.setCharacterSize(20);

	text2.setFont(font3);
	text2.setString(L"О программе");
	text2.setPosition(310, 340);
	text2.setCharacterSize(20);

	text3.setFont(font3);
	text3.setString(L"Выход");
	text3.setPosition(350, 400);
	text3.setCharacterSize(20);

	Sprite  about(aboutTexture), Menu(menutexture);
	bool isMenu = 1;
	int menuNum = 0;

	while (isMenu)
	{


		text1.setColor(Color::Black);
		text1.setScale(Vector2f(1.f, 1.f));
		text1.setOrigin(Vector2f(60, 40));
		text1.setCharacterSize(35);
		text1.setPosition(295, 280);

		text2.setColor(Color::Black);
		text2.setScale(Vector2f(1.f, 1.f));
		text2.setOrigin(Vector2f(60, 40));
		text2.setCharacterSize(35);
		text2.setPosition(280, 340);

		text3.setColor(Color::Black);
		text3.setScale(Vector2f(1.f, 1.f));
		text3.setOrigin(Vector2f(40, 40));
		text3.setCharacterSize(35);
		text3.setPosition(340, 400);

		menuNum = 0;

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				isMenu = false;
			}
		}

		if (IntRect(235, 245, 330, 40).contains(Mouse::getPosition(window))) { text1.setCharacterSize(50); text1.setPosition(228, 265); menuNum = 1; }
		if (IntRect(220, 305, 350, 40).contains(Mouse::getPosition(window))) { text2.setCharacterSize(50); text2.setPosition(203, 325); menuNum = 2; }
		if (IntRect(305, 365, 175, 40).contains(Mouse::getPosition(window))) { text3.setCharacterSize(50); text3.setPosition(305, 390); menuNum = 3; }

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;
			if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3) { window.close(); isMenu = false; }

		}
		
		window.draw(Menu);
		window.draw(text1);
		window.draw(text2);
		window.draw(text3);

		window.display();
	}
}

//Функция окна победы
void WIN(RenderWindow & window)
{

	Texture winscreen;

	winscreen.loadFromFile("images/ПОБЕДА.png");

	Sprite win(winscreen);

	bool isMenu = 1;
	int menuNum = 0;

	while (isMenu)
	{

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				isMenu = false;
			}
		}

		window.draw(win);
		window.display();
	}
}

//Функция окна проигрыша
void LOSE(RenderWindow & window)
{
	Texture losescreen;

	losescreen.loadFromFile("images/ПРОИГРЫШ.png");

	Sprite lose(losescreen);

	bool isMenu = 1;
	int menuNum = 0;

	while (isMenu)
	{

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				isMenu = false;
			}
		}

		window.draw(lose);
		window.display();
	}
}

//Функция проверки выбранной буквы
int proverkabukvi(char simvol, char *slovo, bool *proverka, int &oshibki, int &pravilno, int &schetPovtor, int &dlinaPovtorSimvol, char *povtorSimvol, int &prov, int &num, int &simvolnumber, int mass[], int razmer)
{
	char alphavit[66] = { 'а', 'б', 'в', 'г', 'д', 'е', 'ё', 'ж', 'з', 'и', 'й', 'к', 'л', 'м', 'н', 'о', 'п', 'р', 'с', 'т', 'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'ь', 'ы', 'ъ', 'э', 'ю', 'я' };
	int pos, pos1, sad = 0;
	int dlina = strlen(slovo);
	bool povtorbukvi = true;

	*proverka = false;

	for (int i = 0; i < dlinaPovtorSimvol; i++)
		if (simvol == povtorSimvol[i])
		{
			povtorbukvi = false;
			prov = 3;
			return 0;
		}

	for (int i = 0; i < dlina; i++)
		if (simvol == slovo[i])
			num++;

	for (int i = 0; i < num; i++)
	{
		for (sad; sad < dlina; sad++)
		{
			if (simvol == slovo[sad])
			{
				pravilno++;
				*proverka = true;
				pos = sad + 1;
				prov = 1;
				break;
			}
		}

		//Ищем позицию выбранной буквы и задаем ей координаты
		switch (pos)
		{
		case 1: pos1 = 375 - 20.5*(dlina - 1); break;
		case 2: pos1 = 416 - 20.5*(dlina - 1); break;
		case 3: pos1 = 457 - 20.5*(dlina - 1); break;
		case 4: pos1 = 498 - 20.5*(dlina - 1); break;
		case 5: pos1 = 539 - 20.5*(dlina - 1); break;
		case 6: pos1 = 580 - 20.5*(dlina - 1); break;
		case 7: pos1 = 621 - 20.5*(dlina - 1); break;
		case 8: pos1 = 662 - 20.5*(dlina - 1); break;
		case 9: pos1 = 703 - 20.5*(dlina - 1); break;
		case 10: pos1 = 744 - 20.5*(dlina - 1); break;
		case 11: pos1 = 785 - 20.5*(dlina - 1); break;
		case 12: pos1 = 826 - 20.5*(dlina - 1); break;
		case 13: pos1 = 867 - 20.5*(dlina - 1); break;
		case 14: pos1 = 908 - 20.5*(dlina - 1); break;
		case 15: pos1 = 949 - 20.5*(dlina - 1); break;
		case 16: pos1 = 990 - 20.5*(dlina - 1); break;
		}
		
		mass[i] = pos1;
		sad = sad + 1;
	}

	if (!*proverka)
	{
		oshibki--;
		prov = 2;
	}

	//Запоминаем выбранную букву
	povtorSimvol[schetPovtor] = simvol;
	schetPovtor++;
	dlinaPovtorSimvol = strlen(povtorSimvol);
}

//Основная функция
int main()
{
	RenderWindow window(VideoMode(800, 480), L"Виселица");
	const int razmer = 10;
	char slovo[20], simvol, povtorSimvol[20] = " ";
	int bukva, oshibki = 9, pravilno = 0, schetPovtor = 0, dlinaPovtorSimvol = 0, ver = 0, never = 0, prov = 0, num = 0, simvolnumber = 0, mass[razmer], aa = 0, aaa = 0, aaaa = 0;
	int schetA = 0, schetB = 0, schetV = 0, schetG = 0, schetD = 0, schetE = 0, schetJ = 0, schetZ = 0, schetI1 = 0, schetI2 = 0, schetK = 0, schetL = 0, schetM = 0, schetN = 0, schetO = 0, schetP = 0, schetR = 0, schetS = 0, schetT = 0, schetY = 0, schetF = 0, schetH = 0, schetC = 0, schetCH = 0, schetSH = 0, schetSCH = 0, schetMYA = 0, schetII = 0, schetTV = 0, schetE1 = 0, schetU = 0, schetYA = 0;
	float pos1 = 0;
	bool proverka = false;

	ViborSlova(slovo);

	menu(window);

	Font font3;
	font3.loadFromFile("font/yugothiclight.ttf");

	Text a[16], b[16], v[16], g[16], d[16], e[16], j[16], z[16], i1[16], i2[16], k[16], l[16], m[16], n[16], o[16], p[16], r[16], s[16], t[16], y[16], f[16], h[16], c[16], ch[16], sh[16], sch[16], mya[16], ii[16], tv[16], e1[16], u[16], ya[16];

	Texture texture, blocktexture, Vis1, Vis2, Vis3, Vis4, Vis5, Vis6, Vis7, Vis8, Vis9, Vis10, Verno, Neverno, PovtorVibor;
	texture.loadFromFile("images/ФОН.png");
	blocktexture.loadFromFile("images/block.png");
	blocktexture.setRepeated(true);

	Vis1.loadFromFile("images/1.png");
	Vis2.loadFromFile("images/2.png");
	Vis3.loadFromFile("images/3.png");
	Vis4.loadFromFile("images/4.png");
	Vis5.loadFromFile("images/5.png");
	Vis6.loadFromFile("images/6.png");
	Vis7.loadFromFile("images/7.png");
	Vis8.loadFromFile("images/8.png");
	Vis9.loadFromFile("images/9.png");
	Vis10.loadFromFile("images/10.png");

	Verno.loadFromFile("images/ВЕРНО.png");
	Neverno.loadFromFile("images/НЕВЕРНО.png");
	PovtorVibor.loadFromFile("images/ПОВТОРНЫЙ ВЫБОР.png");

	Sprite block, sprite, vis1, vis2, vis3, vis4, vis5, vis6, vis7, vis8, vis9, vis10, verno, neverno, povtorVibor;
	block.setTexture(blocktexture);
	sprite.setTexture(texture);
	sprite.setPosition(0, 0);

	vis1.setTexture(Vis1);
	vis1.setPosition(100, 185);
	vis2.setTexture(Vis2);
	vis2.setPosition(100, 185);
	vis3.setTexture(Vis3);
	vis3.setPosition(100, 185);
	vis4.setTexture(Vis4);
	vis4.setPosition(100, 185);
	vis5.setTexture(Vis5);
	vis5.setPosition(100, 185);
	vis6.setTexture(Vis6);
	vis6.setPosition(100, 185);
	vis7.setTexture(Vis7);
	vis7.setPosition(100, 185);
	vis8.setTexture(Vis8);
	vis8.setPosition(100, 185);
	vis9.setTexture(Vis9);
	vis9.setPosition(100, 185);
	vis10.setTexture(Vis10);
	vis10.setPosition(100, 185);

	verno.setTexture(Verno);
	verno.setPosition(390, 200);
	neverno.setTexture(Neverno);
	neverno.setPosition(380, 200);
	povtorVibor.setTexture(PovtorVibor);
	povtorVibor.setPosition(370, 200);

	int dlina = strlen(slovo);
	int schet = 41, sdvig = 370;
	for (int i = 0; i < dlina; i++)
	{
		block.setTextureRect({ 0, 0, schet, 50 });
		block.setPosition(sdvig, 100);
		schet = schet + 41;
		sdvig = sdvig - 20;
	}

	for (int i = 0; i < 16; i++) { a[i].setFont(font3); a[i].setString(L"А"); }
	for (int i = 0; i < 16; i++) { b[i].setFont(font3); b[i].setString(L"Б"); }
	for (int i = 0; i < 16; i++) { v[i].setFont(font3); v[i].setString(L"В"); }
	for (int i = 0; i < 16; i++) { g[i].setFont(font3); g[i].setString(L"Г"); }
	for (int i = 0; i < 16; i++) { d[i].setFont(font3); d[i].setString(L"Д"); }
	for (int i = 0; i < 16; i++) { e[i].setFont(font3); e[i].setString(L"Е"); }
	for (int i = 0; i < 16; i++) { j[i].setFont(font3); j[i].setString(L"Ж"); }
	for (int i = 0; i < 16; i++) { z[i].setFont(font3); z[i].setString(L"З"); }
	for (int i = 0; i < 16; i++) { i1[i].setFont(font3); i1[i].setString(L"И"); }
	for (int i = 0; i < 16; i++) { i2[i].setFont(font3); i2[i].setString(L"Й"); }
	for (int i = 0; i < 16; i++) { k[i].setFont(font3); k[i].setString(L"К"); }
	for (int i = 0; i < 16; i++) { l[i].setFont(font3); l[i].setString(L"Л"); }
	for (int i = 0; i < 16; i++) { m[i].setFont(font3); m[i].setString(L"М"); }
	for (int i = 0; i < 16; i++) { n[i].setFont(font3); n[i].setString(L"Н"); }
	for (int i = 0; i < 16; i++) { o[i].setFont(font3); o[i].setString(L"О"); }
	for (int i = 0; i < 16; i++) { p[i].setFont(font3); p[i].setString(L"П"); }
	for (int i = 0; i < 16; i++) { r[i].setFont(font3); r[i].setString(L"Р"); }
	for (int i = 0; i < 16; i++) { s[i].setFont(font3); s[i].setString(L"С"); }
	for (int i = 0; i < 16; i++) { t[i].setFont(font3); t[i].setString(L"Т"); }
	for (int i = 0; i < 16; i++) { y[i].setFont(font3); y[i].setString(L"У"); }
	for (int i = 0; i < 16; i++) { f[i].setFont(font3); f[i].setString(L"Ф"); }
	for (int i = 0; i < 16; i++) { h[i].setFont(font3); h[i].setString(L"Х"); }
	for (int i = 0; i < 16; i++) { c[i].setFont(font3); c[i].setString(L"Ц"); }
	for (int i = 0; i < 16; i++) { ch[i].setFont(font3); ch[i].setString(L"Ч"); }
	for (int i = 0; i < 16; i++) { sh[i].setFont(font3); sh[i].setString(L"Ш"); }
	for (int i = 0; i < 16; i++) { sch[i].setFont(font3); sch[i].setString(L"Щ"); }
	for (int i = 0; i < 16; i++) { mya[i].setFont(font3); mya[i].setString(L"Ь"); }
	for (int i = 0; i < 16; i++) { ii[i].setFont(font3); ii[i].setString(L"Ы"); }
	for (int i = 0; i < 16; i++) { tv[i].setFont(font3); tv[i].setString(L"Ъ"); }
	for (int i = 0; i < 16; i++) { e1[i].setFont(font3); e1[i].setString(L"Э"); }
	for (int i = 0; i < 16; i++) { u[i].setFont(font3); u[i].setString(L"Ю"); }
	for (int i = 0; i < 16; i++) { ya[i].setFont(font3); ya[i].setString(L"Я"); }

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(370, 240, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'а'; bukva = 1; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(418, 240, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'б'; bukva = 2; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(466, 240, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'в'; bukva = 3; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(514, 240, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'г'; bukva = 4; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(562, 240, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'д'; bukva = 5; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(610, 240, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'е'; bukva = 6; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(650, 240, 40, 35).contains(Mouse::getPosition(window))) { simvol = 'ж'; bukva = 7; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(703, 240, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'з'; bukva = 8; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(370, 288, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'и'; bukva = 9; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(418, 288, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'й'; bukva = 10; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(466, 288, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'к'; bukva = 11; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(514, 288, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'л'; bukva = 12; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(560, 288, 32, 35).contains(Mouse::getPosition(window))) { simvol = 'м'; bukva = 13; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(610, 288, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'н'; bukva = 14; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(648, 288, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'о'; bukva = 15; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(703, 288, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'п'; bukva = 16; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(370, 336, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'р'; bukva = 17; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(418, 336, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'с'; bukva = 18; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(466, 336, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'т'; bukva = 19; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(514, 336, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'у'; bukva = 20; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(562, 336, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'ф'; bukva = 21; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(610, 336, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'х'; bukva = 22; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(648, 336, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'ц'; bukva = 23; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(703, 336, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'ч'; bukva = 24; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(365, 384, 40, 35).contains(Mouse::getPosition(window))) { simvol = 'ш'; bukva = 25; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(413, 384, 40, 35).contains(Mouse::getPosition(window))) { simvol = 'щ'; bukva = 26; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(466, 384, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'ь'; bukva = 27; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(511, 384, 35, 35).contains(Mouse::getPosition(window))) { simvol = 'ы'; bukva = 28; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(556, 384, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'ъ'; bukva = 29; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(610, 384, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'э'; bukva = 30; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(650, 384, 40, 35).contains(Mouse::getPosition(window))) { simvol = 'ю'; bukva = 31; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(703, 384, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'я'; bukva = 32; proverkabukvi(simvol, slovo, &proverka, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov, num, simvolnumber, mass, razmer); }

			if (event.type == Event::Closed)
				window.close();
		}

		if (proverka)
		{
			switch (bukva)
			{
			case 1: { for (int i = 0; i < num; i++) { a[i].setCharacterSize(40); a[i].setPosition(mass[i], 100); a[i].setColor(Color::Black); schetA++; } num = 0; } break;
			case 2: { for (int i = 0; i < num; i++) { b[i].setCharacterSize(40); b[i].setPosition(mass[i], 100); b[i].setColor(Color::Black); schetB++; } num = 0; } break;
			case 3: { for (int i = 0; i < num; i++) { v[i].setCharacterSize(40); v[i].setPosition(mass[i], 100); v[i].setColor(Color::Black); schetV++; } num = 0; } break;
			case 4: { for (int i = 0; i < num; i++) { g[i].setCharacterSize(40); g[i].setPosition(mass[i], 100); g[i].setColor(Color::Black); schetG++; } num = 0; } break;
			case 5: { for (int i = 0; i < num; i++) { d[i].setCharacterSize(40); d[i].setPosition(mass[i], 100); d[i].setColor(Color::Black); schetD++; } num = 0; } break;
			case 6: { for (int i = 0; i < num; i++) { e[i].setCharacterSize(40); e[i].setPosition(mass[i], 100); e[i].setColor(Color::Black); schetE++; } num = 0; } break;
			case 7: { for (int i = 0; i < num; i++) { j[i].setCharacterSize(40); j[i].setPosition(mass[i], 100); j[i].setColor(Color::Black); schetJ++; } num = 0; } break;
			case 8: { for (int i = 0; i < num; i++) { z[i].setCharacterSize(40); z[i].setPosition(mass[i], 100); z[i].setColor(Color::Black); schetZ++; } num = 0; } break;
			case 9: { for (int i = 0; i < num; i++) { i1[i].setCharacterSize(40); i1[i].setPosition(mass[i], 100); i1[i].setColor(Color::Black); schetI1++; } num = 0; } break;
			case 10: { for (int i = 0; i < num; i++) { i2[i].setCharacterSize(40); i2[i].setPosition(mass[i], 100); i2[i].setColor(Color::Black); schetI2++; } num = 0; } break;
			case 11: { for (int i = 0; i < num; i++) { k[i].setCharacterSize(40); k[i].setPosition(mass[i], 100); k[i].setColor(Color::Black); schetK++; } num = 0; } break;
			case 12: { for (int i = 0; i < num; i++) { l[i].setCharacterSize(40); l[i].setPosition(mass[i], 100); l[i].setColor(Color::Black); schetL++; } num = 0; } break;
			case 13: { for (int i = 0; i < num; i++) { m[i].setCharacterSize(40); m[i].setPosition(mass[i], 100); m[i].setColor(Color::Black); schetM++; } num = 0; } break;
			case 14: { for (int i = 0; i < num; i++) { n[i].setCharacterSize(40); n[i].setPosition(mass[i], 100); n[i].setColor(Color::Black); schetN++; } num = 0; } break;
			case 15: { for (int i = 0; i < num; i++) { o[i].setCharacterSize(40); o[i].setPosition(mass[i], 100); o[i].setColor(Color::Black); schetO++; } num = 0; } break;
			case 16: { for (int i = 0; i < num; i++) { p[i].setCharacterSize(40); p[i].setPosition(mass[i], 100); p[i].setColor(Color::Black); schetP++; } num = 0; } break;
			case 17: { for (int i = 0; i < num; i++) { r[i].setCharacterSize(40); r[i].setPosition(mass[i], 100); r[i].setColor(Color::Black); schetR++; } num = 0; } break;
			case 18: { for (int i = 0; i < num; i++) { s[i].setCharacterSize(40); s[i].setPosition(mass[i], 100); s[i].setColor(Color::Black); schetS++; } num = 0; } break;
			case 19: { for (int i = 0; i < num; i++) { t[i].setCharacterSize(40); t[i].setPosition(mass[i], 100); t[i].setColor(Color::Black); schetT++; } num = 0; } break;
			case 20: { for (int i = 0; i < num; i++) { y[i].setCharacterSize(40); y[i].setPosition(mass[i], 100); y[i].setColor(Color::Black); schetY++; } num = 0; } break;
			case 21: { for (int i = 0; i < num; i++) { f[i].setCharacterSize(40); f[i].setPosition(mass[i], 100); f[i].setColor(Color::Black); schetF++; } num = 0; } break;
			case 22: { for (int i = 0; i < num; i++) { h[i].setCharacterSize(40); h[i].setPosition(mass[i], 100); h[i].setColor(Color::Black); schetH++; } num = 0; } break;
			case 23: { for (int i = 0; i < num; i++) { c[i].setCharacterSize(40); c[i].setPosition(mass[i], 100); c[i].setColor(Color::Black); schetC++; } num = 0; } break;
			case 24: { for (int i = 0; i < num; i++) { ch[i].setCharacterSize(40); ch[i].setPosition(mass[i], 100); ch[i].setColor(Color::Black); schetCH++; } num = 0; } break;
			case 25: { for (int i = 0; i < num; i++) { sh[i].setCharacterSize(40); sh[i].setPosition(mass[i], 100); sh[i].setColor(Color::Black); schetSH++; } num = 0; } break;
			case 26: { for (int i = 0; i < num; i++) { sch[i].setCharacterSize(40); sch[i].setPosition(mass[i], 100); sch[i].setColor(Color::Black); schetSCH++; } num = 0; } break;
			case 27: { for (int i = 0; i < num; i++) { mya[i].setCharacterSize(40); mya[i].setPosition(mass[i], 100); mya[i].setColor(Color::Black); schetMYA++; } num = 0; } break;
			case 28: { for (int i = 0; i < num; i++) { ii[i].setCharacterSize(40); ii[i].setPosition(mass[i], 100); ii[i].setColor(Color::Black); schetII++; } num = 0; } break;
			case 29: { for (int i = 0; i < num; i++) { tv[i].setCharacterSize(40); tv[i].setPosition(mass[i], 100); tv[i].setColor(Color::Black); schetTV++; } num = 0; } break;
			case 30: { for (int i = 0; i < num; i++) { e1[i].setCharacterSize(40); e1[i].setPosition(mass[i], 100); e1[i].setColor(Color::Black); schetE1++; } num = 0; } break;
			case 31: { for (int i = 0; i < num; i++) { u[i].setCharacterSize(40); u[i].setPosition(mass[i], 100); u[i].setColor(Color::Black); schetU++; } num = 0; } break;
			case 32: { for (int i = 0; i < num; i++) { ya[i].setCharacterSize(40); ya[i].setPosition(mass[i], 100); ya[i].setColor(Color::Black); schetYA++; } num = 0; } break;
			}
		}


		window.clear();
		window.draw(sprite);
		window.draw(block);
		
		for (int i = 0; i < schetA + 1; i++) window.draw(a[i]);
		for (int i = 0; i < schetB + 1; i++) window.draw(b[i]);
		for (int i = 0; i < schetV + 1; i++) window.draw(v[i]);
		for (int i = 0; i < schetG + 1; i++) window.draw(g[i]);
		for (int i = 0; i < schetD + 1; i++) window.draw(d[i]);
		for (int i = 0; i < schetE + 1; i++) window.draw(e[i]);
		for (int i = 0; i < schetJ + 1; i++) window.draw(j[i]);
		for (int i = 0; i < schetZ + 1; i++) window.draw(z[i]);
		for (int i = 0; i < schetI1 + 1; i++) window.draw(i1[i]);
		for (int i = 0; i < schetI2 + 1; i++) window.draw(i2[i]);
		for (int i = 0; i < schetK + 1; i++) window.draw(k[i]);
		for (int i = 0; i < schetL + 1; i++) window.draw(l[i]);
		for (int i = 0; i < schetM + 1; i++) window.draw(m[i]);
		for (int i = 0; i < schetN + 1; i++) window.draw(n[i]);
		for (int i = 0; i < schetO + 1; i++) window.draw(o[i]);
		for (int i = 0; i < schetP + 1; i++) window.draw(p[i]);
		for (int i = 0; i < schetR + 1; i++) window.draw(r[i]);
		for (int i = 0; i < schetS + 1; i++) window.draw(s[i]);
		for (int i = 0; i < schetT + 1; i++) window.draw(t[i]);
		for (int i = 0; i < schetY + 1; i++) window.draw(y[i]);
		for (int i = 0; i < schetF + 1; i++) window.draw(f[i]);
		for (int i = 0; i < schetH + 1; i++) window.draw(h[i]);
		for (int i = 0; i < schetC + 1; i++) window.draw(c[i]);
		for (int i = 0; i < schetCH + 1; i++) window.draw(ch[i]);
		for (int i = 0; i < schetSH + 1; i++) window.draw(sh[i]);
		for (int i = 0; i < schetSCH + 1; i++) window.draw(sch[i]);
		for (int i = 0; i < schetMYA + 1; i++) window.draw(mya[i]);
		for (int i = 0; i < schetII + 1; i++) window.draw(ii[i]);
		for (int i = 0; i < schetTV + 1; i++) window.draw(tv[i]);
		for (int i = 0; i < schetE1 + 1; i++) window.draw(e1[i]);
		for (int i = 0; i < schetU + 1; i++) window.draw(u[i]);
		for (int i = 0; i < schetYA + 1; i++) window.draw(ya[i]);

		if (oshibki == 8) window.draw(vis1);
		if (oshibki == 7) window.draw(vis2);
		if (oshibki == 6) window.draw(vis3);
		if (oshibki == 5) window.draw(vis4);
		if (oshibki == 4) window.draw(vis5);
		if (oshibki == 3) window.draw(vis6);
		if (oshibki == 2) window.draw(vis7);
		if (oshibki == 1) window.draw(vis8);
		if (oshibki == 0) window.draw(vis9);

		if (oshibki == -1) LOSE(window);
		if (pravilno == dlina) WIN(window);

		switch (prov)
		{
		case 1: window.draw(verno); break;
		case 2: window.draw(neverno); break;
		case 3: window.draw(povtorVibor); break;
		}

		window.display();
	}
	return 0;
}