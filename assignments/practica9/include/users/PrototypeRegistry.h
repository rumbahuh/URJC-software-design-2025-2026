/**
 * \author Rebeca Castilla
 * \date 13/12/2025
 * \brief Prototype registry. Stores a single prototype instance per user type.
 *        Uses unique_ptr for automatic memory management.
 */

#ifndef PROTOTYPE_REGISTRY_H
#define PROTOTYPE_REGISTRY_H

#include <memory>
#include "users/User.h"
#include "users/Admin.h"
#include "users/Doctor.h"
#include "users/Pacient.h"

const int N = 4;  // 0 = null, 1 = Admin, 2 = Doctor, 3 = Pacient

class PrototypeRegistry {
public:
    static std::unique_ptr<User> makeUser(int choice);

private:
    static std::unique_ptr<User> userTypes[N];
};

#endif  // PROTOTYPE_REGISTRY_H
