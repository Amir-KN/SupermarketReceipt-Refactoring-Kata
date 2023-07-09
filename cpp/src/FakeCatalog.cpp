//
// Created by sdargo on 2/4/19.
//

#include "FakeCatalog.h"

void FakeCatalog::addProductPrice(const Product& product) {
    products[product.getName()] = product;
}

double FakeCatalog::getProductPrice(const Product& product) {
    return products[product.getName()].getPrice();
}
