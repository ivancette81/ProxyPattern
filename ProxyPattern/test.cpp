#include "pch.h"

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

// Empieza haciendo la clase PlainInternetAccess y pasa el test
// Luego comenta que quieres poner restricciones de acceso y programa el test
// De ahí aparecerá la interfaz y la clase proxy

class IInternetAccess
{
public:
	virtual void goTo(std::string &) = 0;
};

class PlainInternetAccess: public IInternetAccess
{
public:
	PlainInternetAccess()
	{

	}
	void goTo(std::string &URL)
	{
		std::cout << "Accediendo a " << URL << std::endl;
	}
};

class ProxyInternetAccess : public IInternetAccess
{
	PlainInternetAccess * internetAccess;

public:
	ProxyInternetAccess(PlainInternetAccess* internetAccess)
	{
		this->internetAccess = internetAccess;
	}

	~ProxyInternetAccess()
	{
		delete internetAccess;
	}

	void goTo(std::string &URL)
	{
		if (URL.compare("www.google.com")==0) throw "Forbidden!";
	
		internetAccess->goTo(URL);
	}
};


TEST(TestProxyPattern, ProxyPattern) {

	IInternetAccess *internetAccess = new ProxyInternetAccess(new PlainInternetAccess());
	
	std::string URL("www.google.com");
	EXPECT_THROW(internetAccess->goTo(URL), const char *);
	URL.assign("www.bing.com");
	EXPECT_NO_THROW(internetAccess->goTo(URL));


	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}