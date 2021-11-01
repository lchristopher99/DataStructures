//
//  patient.h
//  PriorityQueue
//
//  Created by Logan Christopher on 3/29/20.
//  Copyright © 2020 Logan Christopher. All rights reserved.
//

#ifndef patient_h
#define patient_h

#include <iostream>

struct patient {
    std::string fName;
    std::string lName;
    std::string priority;
    int TicketNum;
    std::string complaint;
    std::string symptoms[20];
};

#endif /* patient_h */
