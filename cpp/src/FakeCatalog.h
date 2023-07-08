#ifndef CPP_FAKECATALOG_H
#define CPP_FAKECATALOG_H


#include <map>
#include "SupermarketCatalog.h"

class FakeCatalog : public SupermarketCatalog {
public:

    void addProduct(const Product& product) override;

    double getUnitPrice(const Product& product) override;

private:
    std::map<std::string, Product> products;
};


#endif //CPP_FAKECATALOG_H
