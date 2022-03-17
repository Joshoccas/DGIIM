/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <string>
#include "DateTime.h"
#include "Event.h"
#include "EventSet.h"
#include "Index.h"
#include "gtest/gtest.h"
#include "datatools.h"
#include "MPTests.h"
using namespace std;

#define NOPS 4
#define MAXUSERS NOPS
#define MAXBRANDS NOPS
#define NUSER(number, B, U) (number / B)
#define NBRAND(number, B, U) (number % B)
#define USER(number, B, U) "User_" + format("%03d", NUSER(number, B, U))
#define BRAND(number, B, U) "Brand_" +format("%03d", NBRAND(number, B, U))

EventSet & IndexBuild(EventSet &es, int B, int U) {
    Event one;
    string date;
    date = "2021-03-01 10:32:00 UTC";
    for (int i = 0; i < B * U; i++) {
        date[8] = STR(1 + NBRAND(i, B, U))[0];
        date[9] = STR(1 + NBRAND(i, B, U))[1];
        one.setDateTime(date);
        one.setBrand(BRAND(i, B, NUSERS)); /// Interleave all brands
        one.setPrice(1 + i % B); /// Fixes the price equals to the brand
        one.setUserID(USER(i, B, U)); /// Groups the users in continuous blocks
        one.setProductID((string) "Product_" + std::to_string(i % B) + "_" + std::to_string(i / B)); // Each brand has exactly 2 products
        one.setSession((string) "Session_" + std::to_string(i / U) + "_" + std::to_string(i));
        one.setType(VALID_TYPES[(i / ((B * U) / 4)) % 4]);
        es.add(one);
    }
    return es;
}

string printIndex(const EventSet &es, const Index &in) {
    string res = "";

    for (int i = 0; i < in.size(); i++) {
        res += es.at(in.at(i).getPos()).to_string() + "\n";
    }
    return res;
}

TEST_F(_01_Basics, Index_Constructors) {
    Index i;

    SKIP_ASSERT_EQ_R(0, i.size()) << " A newly created instance of Index must have size = 0" << endl;
    SKIP_ASSERT_STREQ_R(": On brand? 0", i.to_string().c_str()) << " A newly created instance of Index must write as \": On brand? 0\"" << endl;
}

TEST_F(_02_Intermediate, Index_3x3_just_build) {
    EventSet es;
    Index ies;
    string hashexpected, hashreal, uniques[MAXEVENT];
    es = IndexBuild(es, 3, 3);
    ies.build(es, 0);
    hashreal = ies.reportData();
    ies.build(es, 0);
    hashexpected = ies.reportData();
    SKIP_ASSERT_STREQ_R(hashexpected.c_str(), hashreal.c_str()) << "In any case, building the same index twice gives the same result" << endl;
    ies.build(es, 0);
    hashexpected = ": On brand? 0 : User_000 0 : User_000 1 : User_000 2 : User_001 3 : User_001 4 : User_001 5 : User_002 6 : User_002 7 : User_002 8"; 
    hashreal = ies.to_string();
    CLEANUP(hashreal);
    SKIP_ASSERT_STREQ_R(hashexpected.c_str(), hashreal.c_str()) << "The index by user built within experiment 3x3 differs from the expected one" << endl;
    ies.build(es, 1);
    hashexpected = ": On brand? 1 : Brand_000 0 : Brand_000 3 : Brand_000 6 : Brand_001 1 : Brand_001 4 : Brand_001 7 : Brand_002 2 : Brand_002 5 : Brand_002 8";
    hashreal = ies.to_string();
    CLEANUP(hashreal);
    SKIP_ASSERT_STREQ_R(hashexpected.c_str(), hashreal.c_str()) << "The index by brand built within experiment 3x3 differs from the expected one" << endl;

}

TEST_F(_01_Basics, Index_getIOnWhich) {
    EventSet es;
    string hashexpected, hashreal, uniques[MAXEVENT];
    int key;

    es = IndexBuild(es, 10, 10);
    key = 0;
    Index ies_0(key);
    SKIP_ASSERT_EQ_R(key, ies_0.getIOnWhich()) << "Building an index by Users reports 0" << endl;
    key = 1;
    Index ies_1(key);
    SKIP_ASSERT_EQ_R(key, ies_1.getIOnWhich()) << "Building an index by brand reports 1" << endl;
}

TEST_F(_01_Basics, Index_clear) {
    EventSet es;
    Index ies;
    string hashexpected, hashreal, uniques[MAXEVENT];

    hashexpected = ies.reportData();
    ies.clear();
    hashreal = ies.reportData();
    SKIP_ASSERT_EQ_R(0, ies.size()) << "Clearing a brand new instance of Index leaves it empty" << endl;
    es = IndexBuild(es, 10, 10);
    ies.build(es, 1);
    ies.clear();
    SKIP_ASSERT_EQ_R(0, ies.size()) << "Clearing an instance of Index with existing records leaves it empty" << endl;
}

TEST_F(_02_Intermediate, Index_B_BxU_build_at) {
    EventSet es;
    Index ies;
    string hashexpected, hashreal, uniques[MAXEVENT];
    int B = MAXBRANDS, U = MAXUSERS;
    es = IndexBuild(es, B, U);
    ies.build(es, 1);
    int i = 0;
    for (int b = 0; b < B - 1; b++) {
        for (int u = 0; u < U - 1; i++, u++) {
            SKIP_ASSERT_STREQ_R(ies.at(i).getKey().c_str(), ies.at(i + 1).getKey().c_str()) << i << " The index by brand built within experiment BxU is the same key during U consecutive positions" << endl;
            SKIP_ASSERT_EQ_R(ies.at(i).getPos(), ies.at(i + 1).getPos() - B) << i << " The index by brand built within experiment BxU two consecutive indexes of the same brand differ in B units" << endl;
        }
        SKIP_ASSERT_STRNE_R(ies.at(i).getKey().c_str(), ies.at(i + 1).getKey().c_str()) << i << " The index by user built within experiment BxU changes the key at point U" << endl;
        i++;
    }
}

TEST_F(_02_Intermediate, Index_U_BxU_build_at) {
    EventSet es;
    Index ies;
    string hashexpected, hashreal, uniques[MAXEVENT];
    int B = MAXBRANDS, U = MAXUSERS;
    es = IndexBuild(es, B, U);
    ies.build(es, 0);
    int i = 0;
    for (int u = 0; u < U - 1; u++) {
        for (int b = 0; b < B - 1; i++, b++) {
            SKIP_ASSERT_STREQ_R(ies.at(i).getKey().c_str(), ies.at(i + 1).getKey().c_str()) << i << " The index by user built within experiment BxU is the same key during B consecutive positions" << endl;
            SKIP_ASSERT_EQ_R(ies.at(i).getPos(), ies.at(i + 1).getPos() - 1) << i << " The index by user built within experiment BxU indexes B consecutive positions for the same key" << endl;
        }
        SKIP_ASSERT_STRNE_R(ies.at(i).getKey().c_str(), ies.at(i + 1).getKey().c_str()) << i << " The index by user built within experiment BxU changes the key at point B" << endl;
        i++;
    }
}

TEST_F(_03_Advanced, Index_U_BxU_bounds) {
    EventSet es;
    Index ies;
    string hashexpected, hashreal, uniques[MAXEVENT], user;
    int B = MAXBRANDS, U = MAXUSERS;
    es = IndexBuild(es, B, U);
    ies.build(es, 0);
    int lb = 0, ub;
    for (int u = 0; u < 1 /* U + 1 */; u++) {
        user = (string) "User_" + format("%03d", u);
        lb = u*B;
        ub = std::min((u + 1) * B, B * U);
        ASSERT_EQ_R(u*B, ies.lower_bound(user)) << lb << " The index by user built within experiment BxU lower bounds User u with u*B" << endl;
        ASSERT_EQ_R(std::min((u + 1) * B, B * U), ies.upper_bound(user)) << lb << " The index by user built within experiment BxU upper bounds User u with (u+1)*B" << endl;
    }
}

TEST_F(_03_Advanced, Index_B_BxU_bounds) {
    EventSet es;
    Index ies;
    string hashexpected, hashreal, uniques[MAXEVENT], brand;
    int B = MAXBRANDS, U = MAXUSERS;
    es = IndexBuild(es, B, U);
    ies.build(es, 1);
    int lb = 0, ub;
    for (int b = 0; b < 1 /* B + 1 */; b++) {
        brand = (string) "Brand_" + format("%03d", b);
        lb = b*U;
        ub = std::min((b + 1) * U, B * U);
        ASSERT_EQ_R(b*U, ies.lower_bound(brand)) << lb << " The index by brand built within experiment BxU lower bounds Brand b with b*U" << endl;
        ASSERT_EQ_R(std::min((b + 1) * U, B * U), ies.upper_bound(brand)) << lb << " The index by brand built within experiment BxU upper bounds Brand b with (b+1)*U" << endl;
    }
}

TEST_F(_03_Advanced, Index_add) {
    EventSet es;
    Index ies;
    string toadd, hashexpected, hashreal, uniques[MAXEVENT], brand;
    int B = MAXBRANDS, U = MAXUSERS, sizebefore, sizeafter,
            lowerbound, upperbound;
    Pair p;
    es = IndexBuild(es, B, U);
    ies.build(es, 1);
    sizebefore = ies.size();
    int lb, ub;
    toadd = "ZZZZZ";
    p.setKey(toadd);
    p.setPos(B * U);
    upperbound = ies.upper_bound(toadd);
    ies.add(p);
    sizeafter = ies.size();
    SKIP_ASSERT_EQ_R(sizebefore + 1, sizeafter) << "Inserting any pair in any index increases its size in one" << endl;
    lowerbound = ies.lower_bound(toadd);
    SKIP_ASSERT_EQ_R(lowerbound, upperbound) << "Adding a  key at the end of the index places the new key in its previous upperbound" << endl;
    toadd = "AAAAA";
    p.setKey(toadd);
    p.setPos(B * U);
    ies.add(p);
    lowerbound = ies.lower_bound(toadd);
    SKIP_ASSERT_EQ_R(0, lowerbound) << "Adding a  key at the beginning of the index gives a lower bound equals to 0 after the insertion" << endl;

}

TEST_F(_03_Advanced, Index_B_BxU_rawFilterIndex) {
    EventSet es;
    Index ies, iesfilter;
    string toadd, hashexpected, hashreal, uniques[MAXEVENT], brand, user;
    int B = MAXBRANDS, U = MAXUSERS, sizebefore, sizeafter,
            lowerbound, upperbound;
    Pair p;
    es = IndexBuild(es, B, U);
    ies.build(es, 1);
    for (int b = 0; b < 1 /* B*/; b++) {
        brand = (string) "Brand_" + format("%03d", b);
        iesfilter = rawFilterIndex(es, ies, "Brand", brand);
        SKIP_ASSERT_EQ_R(U, iesfilter.size()) << "In an Index BxU , filtering the index by brand-i produces an index with exactly size U" << endl;
    }
}

TEST_F(_03_Advanced, Index_U_BxU_rawFilterIndex) {
    EventSet es;
    Index ies, iesfilter;
    string toadd, hashexpected, hashreal, uniques[MAXEVENT], brand, user;
    int B = MAXBRANDS, U = MAXUSERS, sizebefore, sizeafter,
            lowerbound, upperbound;
    Pair p;
    es = IndexBuild(es, B, U);
    ies.build(es, 0);
    for (int u = 0; u < 1 /* U */; u++) {
        user = (string) "User_" + format("%03d", u);
        iesfilter = rawFilterIndex(es, ies, "UserID", user);
        SKIP_ASSERT_EQ_R(B, iesfilter.size()) << "In an Index BxU , filtering the index by user-i produces an index with exactly size B" << endl;
    }
}

TEST_F(_03_Advanced, Index_Type_BxU_rawFilterIndex) {
    EventSet es;
    Index ies, iesfilter;
    string toadd, hashexpected, hashreal, uniques[MAXEVENT], brand, user, field, value;
    int B = MAXBRANDS, U = MAXUSERS, sizebefore, sizeafter,
            lowerbound, upperbound;
    Pair p;
    es = IndexBuild(es, B, U);
    ies.build(es, 0);
    field = "Type";
    for (int t = 0; t < 1 /* 4*/; t++) {
        value = VALID_TYPES[t];
        iesfilter = rawFilterIndex(es, ies, field, value);
        SKIP_ASSERT_EQ_R(B * U / 4, iesfilter.size()) << "In an Index BxU , filtering the index by Type=cart produces an index with exactly size B" << endl;

    }
}

TEST_F(_03_Advanced, Index_DateTime_BxU_rawFilterIndex) {
    EventSet es;
    Index ies, iesfilter;
    string toadd, hashexpected, hashreal, uniques[MAXEVENT], brand, user, field, value;
    int B = MAXBRANDS, U = MAXUSERS, sizebefore, sizeafter,
            lowerbound, upperbound;
    Pair p;
    es = IndexBuild(es, B, U);
    ies.build(es, 0);
    field = "DateTime";
    value = es.at(0).getDateTime().to_string();
    iesfilter = rawFilterIndex(es, ies, field, value);
    SKIP_ASSERT_EQ_R(U, iesfilter.size()) << "In an Index BxU , filtering the index by DateTime equals to the first available date produces an index with exactly size B" << endl;
}

TEST_F(_03_Advanced, Index_BxU_sumPrice) {
    EventSet es;
    Index ies, filter_brand, filter_user, filter_type, iest;
    string toadd, hashexpected, hashreal, uniques[MAXEVENT], brand, user, type, date;
    int B = MAXBRANDS, U = MAXUSERS, sizebefore, sizeafter,
            lowerbound, upperbound, b, u, t, day;
    double sump;
    Pair p;
    es = IndexBuild(es, B, U);
    ies.build(es, 0);
    u = 0;
    user = (string) "User_" + format("%03d", u);
    filter_user = rawFilterIndex(es, ies, "UserID", user);
    SKIP_ASSERT_EQ_R(B * (1 + B) / 2, sumPrice(es, filter_user)) << "Given a BxU Index, a filter by user " << u << " the sum of prices amounts to (U*B)/4*(1+B)/2" << endl;

    ies.build(es, 1);
    b = 0;
    brand = (string) "Brand_" + format("%03d", b);
    filter_brand = rawFilterIndex(es, ies, "Brand", brand);
    SKIP_ASSERT_EQ_R(U * (b + 1), sumPrice(es, filter_brand)) << "Given a BxU Index, a filter by brand " << b << " the sum of prices amounts to U*(b+1)" << endl;
    t = 0;
    type = VALID_TYPES[t];
    filter_type = rawFilterIndex(es, ies, "Type", type);
    SKIP_ASSERT_EQ_R((B * U) / 4 * (1 + B) / 2, sumPrice(es, filter_type)) << "Given a BxU Index, a filter by Type=" << type << " the sum of prices amounts to (B*U)/4*(1+B)/2" << endl;
    date = "2021-03-01 10:32:00 UTC";
    day = 1;
    date[8] = STR(day)[0];
    date[9] = STR(day)[1];
    filter_type = rawFilterIndex(es, ies, "DateTime", es.at(0).getDateTime().to_string());
    SKIP_ASSERT_EQ_R(U*day, sumPrice(es, filter_type)) << "Given a BxU Index, a filter by date=" << date << " the sum of prices amounts to U*day" << endl;
}
