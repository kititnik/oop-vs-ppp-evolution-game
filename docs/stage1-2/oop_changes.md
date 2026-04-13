```diff
 stages/stage1/oop/build/app => /dev/null           | Bin 36480 -> 0 bytes
 stages/{stage1 => stage2}/oop/build/app.out        | Bin 39752 -> 41288 bytes
 stages/{stage1 => stage2}/oop/include/simulation.h |   6 ++-
 .../stage2/oop/include/simulation_context.h        |  15 +++++++
 stages/{stage1 => stage2}/oop/include/tribe.h      |   9 ++++-
 stages/{stage1 => stage2}/oop/include/unit.h       |  17 +++++++-
 .../stage2/oop/include/unit_attacker.h             |  21 ++++++++++
 stages/{stage1 => stage2}/oop/include/warrior.h    |  11 ++++-
 stages/{stage1 => stage2}/oop/include/worker.h     |   4 +-
 stages/{stage1 => stage2}/oop/src/simulation.cpp   |  16 ++++++--
 stages/{stage1 => stage2}/oop/src/tribe.cpp        |  45 +++++++++++++++++++--
 stages/{stage1 => stage2}/oop/src/unit.cpp         |  20 ++++++++-
 stages/{stage1 => stage2}/oop/src/warrior.cpp      |  36 +++++++++++++++--
 stages/{stage1 => stage2}/oop/src/worker.cpp       |  15 +++++--
 14 files changed, 194 insertions(+), 21 deletions(-)

diff --color -ru stages/stage1/oop/include/simulation.h stages/stage2/oop/include/simulation.h
--- stages/stage1/oop/include/simulation.h	2026-04-05 22:08:42
+++ stages/stage2/oop/include/simulation.h	2026-04-13 16:04:55
@@ -3,15 +3,19 @@
 
 #include "tribe.h"
 
+// simulation.h - represents the entire simulation state
 class Simulation {
 private:
-    Tribe _tribe;
+    Tribe _tribe1;
+    Tribe _tribe2;
     int _steps;
     int _unitCount;
 
 public:
     Simulation(int unitCount, int steps);
+    // start simulation
     void run();
+    // generate and add units to tribes
     void createUnits();
 };
 
Only in stages/stage2/oop/include: simulation_context.h
diff --color -ru stages/stage1/oop/include/tribe.h stages/stage2/oop/include/tribe.h
--- stages/stage1/oop/include/tribe.h	2026-04-05 22:08:42
+++ stages/stage2/oop/include/tribe.h	2026-04-13 15:34:31
@@ -4,14 +4,21 @@
 #include <vector>
 #include "unit.h"
 
+struct SimulationContext;
+
+// tribe.h - a tribe is like a collection of units with common resources
 class Tribe {
 private:
     std::vector<std::unique_ptr<Unit>> _units;
+    int _resourcesCount;
 
 public:
     Tribe();
-    void actAll();
+    void actAll(SimulationContext& context);
     void addUnit(std::unique_ptr<Unit> unit);
+    std::optional<std::reference_wrapper<Unit>> getRandomAliveUnit();
+    int getResourcesCount();
+    void setResourcesCount(int resources);
 };
 
 #endif // __tribe__
\ No newline at end of file
diff --color -ru stages/stage1/oop/include/unit.h stages/stage2/oop/include/unit.h
--- stages/stage1/oop/include/unit.h	2026-04-10 17:27:31
+++ stages/stage2/oop/include/unit.h	2026-04-13 15:56:03
@@ -1,13 +1,28 @@
 #ifndef __unit__
 #define __unit__
 
+#include "unit_attacker.h"
+
+struct SimulationContext;
+
+// unit.h - base class representing any unit in the simulation 
 class Unit {
 public:
     int id;
+    int health;
 
 public:
     Unit(int id);
-    virtual void act() = 0;
+    // This method is called when it is the unit's turn in simulation step.
+    virtual void act(SimulationContext& context) = 0;
+    bool isAlive();
+    // This method is called when a unit is under attack.
+    // You should call attacker.attack{your unit type}(e.g. attacker.attackWorker(target)) 
+    // here to get an attack
+    virtual void acceptAttack(UnitAttacker& attacker) = 0;
+    void takeDamage(int damage);
+    int getHealth();
+    int getId();
     virtual ~Unit() = default;
 };
 
Only in stages/stage2/oop/include: unit_attacker.h
diff --color -ru stages/stage1/oop/include/warrior.h stages/stage2/oop/include/warrior.h
--- stages/stage1/oop/include/warrior.h	2026-04-05 22:08:42
+++ stages/stage2/oop/include/warrior.h	2026-04-13 15:50:43
@@ -1,12 +1,19 @@
 #ifndef __warrior__
 #define __warrior__
 
+#include "unit_attacker.h"
 #include "unit.h"
 
-class Warrior : public Unit {
+// warrior.h - derived class from Unit with UnitAttacker abilities
+class Warrior : public Unit, public UnitAttacker {
 public:
+    int damage;
+public:
     Warrior(int id);
-    void act() override;
+    void act(SimulationContext& context) override;
+    void acceptAttack(UnitAttacker& attacker) override;
+    void attackWarrior(Warrior& target) override;
+    void attackWorker(Worker& targer) override;
 };
 
 #endif // __warrior__
\ No newline at end of file
diff --color -ru stages/stage1/oop/include/worker.h stages/stage2/oop/include/worker.h
--- stages/stage1/oop/include/worker.h	2026-04-10 17:22:23
+++ stages/stage2/oop/include/worker.h	2026-04-13 15:48:33
@@ -3,10 +3,12 @@
 
 #include "unit.h"
 
+// worker.h - derived class from Unit
 class Worker : public Unit {
 public:
     Worker(int id);
-    void act() override;
+    void act(SimulationContext& context) override;
+    void acceptAttack(UnitAttacker& attacker) override;
 };
 
 #endif // __worker__
\ No newline at end of file
diff --color -ru stages/stage1/oop/src/simulation.cpp stages/stage2/oop/src/simulation.cpp
--- stages/stage1/oop/src/simulation.cpp	2026-04-05 22:08:42
+++ stages/stage2/oop/src/simulation.cpp	2026-04-13 15:54:01
@@ -1,10 +1,11 @@
 #include "simulation.h"
+#include "simulation_context.h"
 #include "warrior.h"
 #include "worker.h"
 #include <iostream>
 #include <random>
 
-Simulation::Simulation(int unitCount, int steps) : _tribe() {
+Simulation::Simulation(int unitCount, int steps) : _tribe1(), _tribe2() {
     _unitCount = unitCount;
     _steps = steps;
 }
@@ -15,11 +16,14 @@
     for(int i = 0; i < _unitCount; ++i)
     {
         std::uniform_int_distribution<std::mt19937::result_type> dist6(0,1);
+        // The same type of unit is added to both tribes at once
         if(dist6(rng)) {
-            _tribe.addUnit(std::make_unique<Warrior>(i));
+            _tribe1.addUnit(std::make_unique<Warrior>(i));
+            _tribe2.addUnit(std::make_unique<Warrior>(i+_unitCount));
         }
         else {
-            _tribe.addUnit(std::make_unique<Worker>(i));
+            _tribe1.addUnit(std::make_unique<Worker>(i));
+            _tribe2.addUnit(std::make_unique<Worker>(i+_unitCount));
         }
     }
 }
@@ -27,6 +31,10 @@
 void Simulation::run() {
     for (int step = 0; step < _steps; ++step) {
         std::cout << "=== Step " << step << " ===" << std::endl;
-        _tribe.actAll();
+        // Create special context for each tribe
+        SimulationContext contextTribe1 = { _tribe1, _tribe2 };
+        SimulationContext contextTribe2 = { _tribe2, _tribe1 };
+        _tribe1.actAll(contextTribe1);
+        _tribe2.actAll(contextTribe2);
     }
 }
\ No newline at end of file
diff --color -ru stages/stage1/oop/src/tribe.cpp stages/stage2/oop/src/tribe.cpp
--- stages/stage1/oop/src/tribe.cpp	2026-04-05 22:08:42
+++ stages/stage2/oop/src/tribe.cpp	2026-04-13 15:54:21
@@ -1,14 +1,53 @@
 #include "tribe.h"
+#include "simulation_context.h"
+#include <cstddef>
+#include <cstdlib>
+#include <functional>
+#include <memory>
+#include <optional>
 #include <utility>
+#include <vector>
 
-Tribe::Tribe() = default;
+Tribe::Tribe() {
+    _resourcesCount = 0;
+}
 
 void Tribe::addUnit(std::unique_ptr<Unit> unit) {
     _units.push_back(std::move(unit));
 }
 
-void Tribe::actAll() {
+void Tribe::actAll(SimulationContext& context) {
     for (auto& unit : _units) {
-        unit->act();
+        if(!unit->isAlive()) continue;
+        unit->act(context);
     }
+}
+
+std::optional<std::reference_wrapper<Unit>> Tribe::getRandomAliveUnit() {
+    // Two passes: first we count the live ones, then we go to the desired one.
+    // Does not require an additional buffer.
+    size_t aliveCount = 0;
+    for (auto& unit : _units) {
+        if(unit->isAlive()) {
+            aliveCount++;
+        }
+    }
+    if(aliveCount == 0) return std::nullopt;
+
+    size_t target = rand() % aliveCount;
+    for (auto& unit : _units) {
+        if(unit->isAlive()) {
+            if(target == 0) return *unit;
+            target--;
+        }
+    }
+    return std::nullopt;
+}
+
+int Tribe::getResourcesCount() {
+    return _resourcesCount;
+}
+
+void Tribe::setResourcesCount(int resources) {
+    _resourcesCount = std::max(resources, 0);
 }
\ No newline at end of file
diff --color -ru stages/stage1/oop/src/unit.cpp stages/stage2/oop/src/unit.cpp
--- stages/stage1/oop/src/unit.cpp	2026-04-10 17:27:31
+++ stages/stage2/oop/src/unit.cpp	2026-04-10 17:29:30
@@ -2,4 +2,22 @@
 
 Unit::Unit(int id) {
     this->id = id;
-}
\ No newline at end of file
+    this->health = 100;
+}
+
+bool Unit::isAlive() {
+    return (health > 0);
+}
+
+void Unit::takeDamage(int damage) {
+    health -= damage;
+    if(health < 0) health = 0;
+}
+
+int Unit::getHealth() {
+    return health;
+}
+
+int Unit::getId() {
+    return id;
+}
diff --color -ru stages/stage1/oop/src/warrior.cpp stages/stage2/oop/src/warrior.cpp
--- stages/stage1/oop/src/warrior.cpp	2026-04-10 17:27:31
+++ stages/stage2/oop/src/warrior.cpp	2026-04-13 15:21:15
@@ -1,8 +1,36 @@
-#include "warrior.h"
 #include <iostream>
+#include <optional>
+#include "warrior.h"
+#include "simulation_context.h"
+#include "tribe.h"
+#include "worker.h"
 
-Warrior::Warrior(int id) : Unit(id) {}
+Warrior::Warrior(int id) : Unit(id) {
+    damage = 35;
+}
 
-void Warrior::act() {
-    std::cout << "Warrior " << id << " is attacking\n";
+void Warrior::act(SimulationContext& context) {
+    auto target = context.enemyTribe.get().getRandomAliveUnit();
+    if(target == std::nullopt) {
+        std::cout << "Warrior " << id << " didn't find enemy to attack\n";
+        return;
+    }
+    target->get().acceptAttack(*this);
+}
+
+void Warrior::acceptAttack(UnitAttacker& attacker) {
+    attacker.attackWarrior(*this);
+}
+
+// Warrior vs Warrior: damage is halved due to armor
+// damage * 0.5 is an integer truncation
+void Warrior::attackWarrior(Warrior& target) {
+    target.takeDamage(damage * 0.5);
+    std::cout << "Warrior " << id << " is attacking Warrior " << target.getId() << ", target health " << target.getHealth() << "\n";
+}
+
+// Warrior vs Worker: full damage
+void Warrior::attackWorker(Worker& target) {
+    target.takeDamage(damage);
+    std::cout << "Warrior " << id << " is attacking Worker " << target.getId() << ", target health " << target.getHealth() << "\n";
 }
\ No newline at end of file
diff --color -ru stages/stage1/oop/src/worker.cpp stages/stage2/oop/src/worker.cpp
--- stages/stage1/oop/src/worker.cpp	2026-04-10 17:27:31
+++ stages/stage2/oop/src/worker.cpp	2026-04-13 15:04:31
@@ -1,8 +1,17 @@
-#include "worker.h"
 #include <iostream>
+#include "worker.h"
+#include "simulation_context.h"
+#include "tribe.h"
 
 Worker::Worker(int id) : Unit(id) {}
 
-void Worker::act() {
-    std::cout << "Worker " << id << " is working\n";
+void Worker::act(SimulationContext& context) {
+    int foundResources = rand() % 10;
+    auto& ownTribe = context.ownTribe.get();
+    ownTribe.setResourcesCount(foundResources + ownTribe.getResourcesCount());
+    std::cout << "Worker " << id << " found: " << foundResources << "; now have " << ownTribe.getResourcesCount() << "\n";
+}
+
+void Worker::acceptAttack(UnitAttacker& attacker) {
+    attacker.attackWorker(*this);
 }
\ No newline at end of file

```