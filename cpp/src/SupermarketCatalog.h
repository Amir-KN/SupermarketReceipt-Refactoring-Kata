#ifndef CPP_SUPERMARKETCATALOG_H
#define CPP_SUPERMARKETCATALOG_H


#include "Product.h"

class SupermarketCatalog {
public:
    virtual void addProductPrice(const Product& product) = 0;
    virtual double getProductPrice(const Product& product) = 0;
};


#endif //CPP_SUPERMARKETCATALOG_H
