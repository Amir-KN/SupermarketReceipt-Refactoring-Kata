#include "ShoppingCart.h"

void addItemQuantity(const Product& product, double quantity);

std::vector<ProductQuantity> ShoppingCart::getItems() const {
    return items;
}

std::map<Product, double> ShoppingCart::getProductQuantities() const {
    return productQuantities;
}

void ShoppingCart::addItem(const Product& product) {
    addItemQuantity(product, 1.0);
}

void ShoppingCart::addItemQuantity(const Product& product, double quantity) {
    items.emplace_back(product, quantity);
    if (productQuantities.find(product) != productQuantities.end()) {
        productQuantities[product] += quantity;
    } else {
        productQuantities[product] = quantity;
    }
}

void ShoppingCart::handleOffers(Receipt& receipt, std::map<Product, Offer> offers, SupermarketCatalog* catalog) {
    for (const auto& productQuantity : productQuantities) {
        Product product = productQuantity.first;
        double quantity = productQuantity.second;
        if (offers.find(product) != offers.end()) {
            auto offer = offers[product];
            double unitPrice = catalog->getProductPrice(product);
            int quantityAsInt = (int) quantity;
            Discount* discount = nullptr;
            int boughtProductsNum = 1;

            if (offer.getOfferType() == SpecialOfferType::ThreeForTwo) {
                boughtProductsNum = 3;
            } else if (offer.getOfferType() == SpecialOfferType::TwoForAmount) {
                boughtProductsNum = 2;
                if (quantityAsInt >= 2) {
                    double total = offer.getArgument() * (quantityAsInt / boughtProductsNum) + quantityAsInt % 2 * unitPrice;
                    double discountN = unitPrice * quantity - total;
                    discount = new Discount("2 for " + std::to_string(offer.getArgument()), -discountN, product);
                }
            } if (offer.getOfferType() == SpecialOfferType::FiveForAmount) {
                boughtProductsNum = 5;
            }
            int boughtProductsRatio = quantityAsInt / boughtProductsNum;
            if (offer.getOfferType() == SpecialOfferType::ThreeForTwo && quantityAsInt > 2) {
                double discountAmount = quantity * unitPrice - ((boughtProductsRatio * 2 * unitPrice) + quantityAsInt % 3 * unitPrice);
                discount = new Discount("3 for 2", -discountAmount, product);
            }
            if (offer.getOfferType() == SpecialOfferType::TenPercentDiscount) {
                discount = new Discount(std::to_string(offer.getArgument()) + "% off", -quantity * unitPrice * offer.getArgument() / 100.0, product);
            }
            if (offer.getOfferType() == SpecialOfferType::FiveForAmount && quantityAsInt >= 5) {
                double discountTotal = unitPrice * quantity - (offer.getArgument() * boughtProductsRatio + quantityAsInt % 5 * unitPrice);
                discount = new Discount(std::to_string(boughtProductsNum) + " for " + std::to_string(offer.getArgument()), -discountTotal, product);
            }
            if (discount != nullptr)
                receipt.addDiscount(*discount);
        }
    }
}