#include <SFML/Graphics.hpp>
#include "iostream"
#include "string"
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <ctime>
#include <sstream>
#pragma warning(disable : 4996)
using namespace std;
using namespace sf;

//Функция выбора случайного слова
char ViborSlova(char slovo[20])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

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
	//Загрузка шрифта
	Font font1, font2, font3;
	font1.loadFromFile("font/10460.ttf");
	font2.loadFromFile("font/11814.ttf");
	font3.loadFromFile("font/yugothiclight.ttf");

	Text text1, text2, text3;
	
	//Выбираем шрифт
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


		if (IntRect(235, 245, 330, 40).contains(Mouse::getPosition(window))) { text1.setCharacterSize(50); text1.setPosition(228, 265); menuNum = 1; }
		if (IntRect(220, 305, 350, 40).contains(Mouse::getPosition(window))) { text2.setCharacterSize(50); text2.setPosition(203, 325); menuNum = 2; }
		if (IntRect(305, 365, 175, 40).contains(Mouse::getPosition(window))) { text3.setCharacterSize(50); text3.setPosition(305, 390); menuNum = 3; }
		
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1) isMenu = false;
			if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3) { window.close(); isMenu = false; }

		}

		//Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
		//cout << pixelPos.x << "  " << pixelPos.y << "\n";//смотрим на координату Х позиции курсора в консоли (она не будет больше ширины окна)

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
int proverkabukvi(char simvol, char *slovo, bool *proverka, float *pos1, int &oshibki, int &pravilno, int &schetPovtor, int &dlinaPovtorSimvol, char *povtorSimvol, int &prov)
	{
		cout << simvol << "\n";
		cout << slovo << "\n";
		char alphavit[66] = { 'а', 'б', 'в', 'г', 'д', 'е', 'ё', 'ж', 'з', 'и', 'й', 'к', 'л', 'м', 'н', 'о', 'п', 'р', 'с', 'т', 'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'ь', 'ы', 'ъ', 'э', 'ю', 'я' };
		int pos;
		int dlina = strlen(slovo);
		bool povtorbukvi = true;

		*proverka = false;

		for (int i = 0; i < dlinaPovtorSimvol; i++)
			if (simvol == povtorSimvol[i])
			{
				cout << "\nЭта буква уже была введена. Введите другую букву.\n\n";
				povtorbukvi = false;
				prov = 3;
				return 0;
			}

		for (int i = 0; i < dlina; i++)
		{
			if (simvol == slovo[i])
			{
				pravilno++;
				*proverka = true;
				pos = i + 1;
				cout << "Правильно " << pravilno << "\n";
				prov = 1;
			}
		}

		if (!*proverka)
		{
			cout << "Нет, такой буквы в загаданом слове нет.\n\n";
			oshibki--;
			cout << "Ошибки " << oshibki << "\n";
			prov = 2;
		}

		//Запоминаем выбранную букву
		povtorSimvol[schetPovtor] = simvol;
		schetPovtor++;
		dlinaPovtorSimvol = strlen(povtorSimvol);

		//Ищем позицию выбранной буквы и задаем ей координаты
		switch (pos)
		{
		case 1: *pos1 = 375 - 20.5*(dlina - 1); break;
		case 2: *pos1 = 416 - 20.5*(dlina - 1); break;
		case 3: *pos1 = 457 - 20.5*(dlina - 1); break;
		case 4: *pos1 = 498 - 20.5*(dlina - 1); break;
		case 5: *pos1 = 539 - 20.5*(dlina - 1); break;
		case 6: *pos1 = 580 - 20.5*(dlina - 1); break;
		case 7: *pos1 = 621 - 20.5*(dlina - 1); break;
		case 8: *pos1 = 662 - 20.5*(dlina - 1); break;
		case 9: *pos1 = 703 - 20.5*(dlina - 1); break;
		case 10: *pos1 = 744 - 20.5*(dlina - 1); break;
		case 11: *pos1 = 785 - 20.5*(dlina - 1); break;
		case 12: *pos1 = 826 - 20.5*(dlina - 1); break;
		case 13: *pos1 = 867 - 20.5*(dlina - 1); break;
		case 14: *pos1 = 908 - 20.5*(dlina - 1); break;
		case 15: *pos1 = 949 - 20.5*(dlina - 1); break;
		case 16: *pos1 = 990 - 20.5*(dlina - 1); break;
		}

		if (pravilno == dlina)
		{
			cout << "Поздравляю, вы угадали слово!\n";
			cout << "Слово было следующим: \"";
			cout << slovo;
			cout << "\".\n";
			cout << "Спасибо за игру!\n";
		}

		if (oshibki < 0)
		{
			cout << "\nУвы, вы превысили лимит допустимых ошибок.\n";
			cout << "Слово было следующим: \"";
			cout << slovo;
			cout << "\".\n";
			cout << "Спасибо за игру!\n";
		}
 }
	
//Основная функция
int main()
{
	RenderWindow window(VideoMode(800, 480), "Game");
	
	char slovo[20], simvol, povtorSimvol[20] = " ";
	int bukva, oshibki = 9, pravilno = 0, schetPovtor = 0, dlinaPovtorSimvol = 0, ver = 0, never = 0, prov = 0;
	float pos1 = 0;
	bool proverka = false;

	ViborSlova(slovo);

	menu(window);

	Font font3;
	font3.loadFromFile("font/yugothiclight.ttf");

	Text a, b, v, g, d, e, j, z, i, i1, k, l, m, n, o, p, r, s, t, y, f, h, c, ch, sh, sch, mya, ii, tv, e1, u, ya;

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
	
	a.setFont(font3);
	a.setString(L"А");

	b.setFont(font3);
	b.setString(L"Б");

	v.setFont(font3);
	v.setString(L"В");

	g.setFont(font3);
	g.setString(L"Г");

	d.setFont(font3);
	d.setString(L"Д");

	e.setFont(font3);
	e.setString(L"Е");

	j.setFont(font3);
	j.setString(L"Ж");

	z.setFont(font3);
	z.setString(L"З");

	i.setFont(font3);
	i.setString(L"И");

	i1.setFont(font3);
	i1.setString(L"Й");

	k.setFont(font3);
	k.setString(L"К");

	l.setFont(font3);
	l.setString(L"Л");

	m.setFont(font3);
	m.setString(L"М");

	n.setFont(font3);
	n.setString(L"Н");

	o.setFont(font3);
	o.setString(L"О");

	p.setFont(font3);
	p.setString(L"П");

	r.setFont(font3);
	r.setString(L"Р");

	s.setFont(font3);
	s.setString(L"С");

	t.setFont(font3);
	t.setString(L"Т");

	y.setFont(font3);
	y.setString(L"У");

	f.setFont(font3);
	f.setString(L"Ф");

	h.setFont(font3);
	h.setString(L"Х");

	c.setFont(font3);
	c.setString(L"Ц");

	ch.setFont(font3);
	ch.setString(L"Ч");

	sh.setFont(font3);
	sh.setString(L"Ш");

	sch.setFont(font3);
	sch.setString(L"Щ");

	mya.setFont(font3);
	mya.setString(L"Ь");

	ii.setFont(font3);
	ii.setString(L"Ы");

	tv.setFont(font3);
	tv.setString(L"Ъ");

	e1.setFont(font3);
	e1.setString(L"Э");

	u.setFont(font3);
	u.setString(L"Ю");

	ya.setFont(font3);
	ya.setString(L"Я");
	
	Clock clock;

	while (window.isOpen())
	{
		Event event1;
		while (window.pollEvent(event1))
		{
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(370, 240, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'а'; bukva = 1; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(418, 240, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'б'; bukva = 2; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(466, 240, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'в'; bukva = 3; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(514, 240, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'г'; bukva = 4; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(562, 240, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'д'; bukva = 5; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(610, 240, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'е'; bukva = 6; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(650, 240, 40, 35).contains(Mouse::getPosition(window))) { simvol = 'ж'; bukva = 7; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(703, 240, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'з'; bukva = 8; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(370, 288, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'и'; bukva = 9; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(418, 288, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'й'; bukva = 10; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(466, 288, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'к'; bukva = 11; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(514, 288, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'л'; bukva = 12; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(560, 288, 32, 35).contains(Mouse::getPosition(window))) { simvol = 'м'; bukva = 13; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(610, 288, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'н'; bukva = 14; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(648, 288, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'о'; bukva = 15; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(703, 288, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'п'; bukva = 16; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(370, 336, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'р'; bukva = 17; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(418, 336, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'с'; bukva = 18; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(466, 336, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'т'; bukva = 19; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(514, 336, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'у'; bukva = 20; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(562, 336, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'ф'; bukva = 21; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(610, 336, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'х'; bukva = 22; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(648, 336, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'ц'; bukva = 23; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(703, 336, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'ч'; bukva = 24; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(365, 384, 40, 35).contains(Mouse::getPosition(window))) { simvol = 'ш'; bukva = 25; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(413, 384, 40, 35).contains(Mouse::getPosition(window))) { simvol = 'щ'; bukva = 26; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(466, 384, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'ь'; bukva = 27; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(511, 384, 35, 35).contains(Mouse::getPosition(window))) { simvol = 'ы'; bukva = 28; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(556, 384, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'ъ'; bukva = 29; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(610, 384, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'э'; bukva = 30; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(650, 384, 40, 35).contains(Mouse::getPosition(window))) { simvol = 'ю'; bukva = 31; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }
			if ((Mouse::isButtonPressed(Mouse::Left)) && IntRect(703, 384, 30, 35).contains(Mouse::getPosition(window))) { simvol = 'я'; bukva = 32; proverkabukvi(simvol, slovo, &proverka, &pos1, oshibki, pravilno, schetPovtor, dlinaPovtorSimvol, povtorSimvol, prov); }		
		}

		switch (bukva)
		{
		case 1: if (proverka) { a.setCharacterSize(40); a.setPosition(pos1, 100); a.setColor(Color::Black); } break;
		case 2: if (proverka) { b.setCharacterSize(40); b.setPosition(pos1, 100); b.setColor(Color::Black); } break;
		case 3: if (proverka) { v.setCharacterSize(40); v.setPosition(pos1, 100); v.setColor(Color::Black); } break;
		case 4: if (proverka) { g.setCharacterSize(40); g.setPosition(pos1, 100); g.setColor(Color::Black); } break;
		case 5: if (proverka) { d.setCharacterSize(40); d.setPosition(pos1, 100); d.setColor(Color::Black); } break;
		case 6: if (proverka) { e.setCharacterSize(40); e.setPosition(pos1, 100); e.setColor(Color::Black); } break;
		case 7: if (proverka) { j.setCharacterSize(40); j.setPosition(pos1, 100); j.setColor(Color::Black); } break;
		case 8: if (proverka) { z.setCharacterSize(40); z.setPosition(pos1, 100); z.setColor(Color::Black); } break;
		case 9: if (proverka) { i.setCharacterSize(40); i.setPosition(pos1, 100); i.setColor(Color::Black); } break;
		case 10: if (proverka) { i1.setCharacterSize(40); i1.setPosition(pos1, 100); i1.setColor(Color::Black); } break;
		case 11: if (proverka) { k.setCharacterSize(40); k.setPosition(pos1, 100); k.setColor(Color::Black); } break;
		case 12: if (proverka) { l.setCharacterSize(40); l.setPosition(pos1, 100); l.setColor(Color::Black); } break;
		case 13: if (proverka) { m.setCharacterSize(40); m.setPosition(pos1, 100); m.setColor(Color::Black); } break;
		case 14: if (proverka) { n.setCharacterSize(40); n.setPosition(pos1, 100); n.setColor(Color::Black); } break;
		case 15: if (proverka) { o.setCharacterSize(40); o.setPosition(pos1, 100); o.setColor(Color::Black); } break;
		case 16: if (proverka) { p.setCharacterSize(40); p.setPosition(pos1, 100); p.setColor(Color::Black); } break;
		case 17: if (proverka) { r.setCharacterSize(40); r.setPosition(pos1, 100); r.setColor(Color::Black); } break;
		case 18: if (proverka) { s.setCharacterSize(40); s.setPosition(pos1, 100); s.setColor(Color::Black); } break;
		case 19: if (proverka) { t.setCharacterSize(40); t.setPosition(pos1, 100); t.setColor(Color::Black); } break;
		case 20: if (proverka) { y.setCharacterSize(40); y.setPosition(pos1, 100); y.setColor(Color::Black); } break;
		case 21: if (proverka) { f.setCharacterSize(40); f.setPosition(pos1, 100); f.setColor(Color::Black); } break;
		case 22: if (proverka) { h.setCharacterSize(40); h.setPosition(pos1, 100); h.setColor(Color::Black); } break;
		case 23: if (proverka) { c.setCharacterSize(40); c.setPosition(pos1, 100); c.setColor(Color::Black); } break;
		case 24: if (proverka) { ch.setCharacterSize(40); ch.setPosition(pos1, 100); ch.setColor(Color::Black); } break;
		case 25: if (proverka) { sh.setCharacterSize(40); sh.setPosition(pos1, 100); sh.setColor(Color::Black); } break;
		case 26: if (proverka) { sch.setCharacterSize(40); sch.setPosition(pos1, 100); sch.setColor(Color::Black); } break;
		case 27: if (proverka) { mya.setCharacterSize(40); mya.setPosition(pos1, 100); mya.setColor(Color::Black); } break;
		case 28: if (proverka) { ii.setCharacterSize(40); ii.setPosition(pos1, 100); ii.setColor(Color::Black); } break;
		case 29: if (proverka) { tv.setCharacterSize(40); tv.setPosition(pos1, 100); tv.setColor(Color::Black); } break;
		case 30: if (proverka) { e1.setCharacterSize(40); e1.setPosition(pos1, 100); e1.setColor(Color::Black); } break;
		case 31: if (proverka) { u.setCharacterSize(40); u.setPosition(pos1, 100); u.setColor(Color::Black); } break;
		case 32: if (proverka) { ya.setCharacterSize(40); ya.setPosition(pos1, 100); ya.setColor(Color::Black); } break;
		}

		//Координаты мыши
		//Vector2i pixelPos = Mouse::getPosition(window);//забираем коорд курсора
		//cout << pixelPos.x << "  " << pixelPos.y << "\n";//смотрим на координату Х позиции курсора в консоли (она не будет больше ширины окна)

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(sprite);
		window.draw(block);

		window.draw(a);
		window.draw(b);
		window.draw(v);
		window.draw(g);
		window.draw(d);
		window.draw(e);
		window.draw(e1);
		window.draw(j);
		window.draw(z);
		window.draw(i);
		window.draw(i1);
		window.draw(k);
		window.draw(l);
		window.draw(m);
		window.draw(n);
		window.draw(o);
		window.draw(p);
		window.draw(r);
		window.draw(s);
		window.draw(t);
		window.draw(y);
		window.draw(f);
		window.draw(h);
		window.draw(c);
		window.draw(ch);
		window.draw(sh);
		window.draw(sch);
		window.draw(mya);
		window.draw(ii);
		window.draw(tv);
		window.draw(e1);
		window.draw(u);
		window.draw(ya);

		if (oshibki == 8)
			window.draw(vis1);
		if (oshibki == 7)
			window.draw(vis2);
		if (oshibki == 6)
			window.draw(vis3);
		if (oshibki == 5)
			window.draw(vis4);
		if (oshibki == 4)
			window.draw(vis5);
		if (oshibki == 3)
			window.draw(vis6);
		if (oshibki == 2)
			window.draw(vis7);
		if (oshibki == 1)
			window.draw(vis8);
		if (oshibki == 0)
			window.draw(vis9);

		if (oshibki == -1)
			LOSE(window);
		if (pravilno == dlina)
			WIN(window);

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