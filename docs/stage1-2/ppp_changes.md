```diff
 stages/{stage1 => stage2}/ppp/.DS_Store            | Bin 6148 -> 6148 bytes
 stages/{stage1 => stage2}/ppp/build/app.out        | Bin 32328 -> 32968 bytes
 stages/{stage1 => stage2}/ppp/include/container.h  |   6 ++--
 stages/{stage1 => stage2}/ppp/include/simulation.h |   2 ++
 .../stage2/ppp/include/simulation_context.h        |  13 +++++++
 stages/{stage1 => stage2}/ppp/include/tribe.h      |   7 +++-
 stages/{stage1 => stage2}/ppp/include/unit.h       |  14 ++++----
 stages/{stage1 => stage2}/ppp/include/warrior.h    |  13 ++++++-
 stages/{stage1 => stage2}/ppp/include/worker.h     |   6 +++-
 stages/{stage1 => stage2}/ppp/src/simulation.c     |  39 +++++++++++++++------
 stages/{stage1 => stage2}/ppp/src/tribe.c          |  33 +++++++++++++++--
 stages/{stage1 => stage2}/ppp/src/unit.c           |  15 +++++++-
 stages/{stage1 => stage2}/ppp/src/warrior.c        |  31 +++++++++++++---
 stages/{stage1 => stage2}/ppp/src/worker.c         |   9 ++---
 14 files changed, 153 insertions(+), 35 deletions(-)

diff --color -ru stages/stage1/ppp/include/container.h stages/stage2/ppp/include/container.h
--- stages/stage1/ppp/include/container.h	2026-04-05 22:08:42
+++ stages/stage2/ppp/include/container.h	2026-04-13 15:59:02
@@ -4,12 +4,10 @@
 #include "ppvector.h"
 
 //==============================================================================
-// container.h - содержит тип данных,
-// представляющий простейший контейнер
+// container.h - comtains datatype for vector
 //==============================================================================
 //------------------------------------------------------------------------------
-// Ссылка на описание геометрической фигуры. Знание структуры самой фигуры
-// для представленной реализации контейнера не требуется
+// Unit struct declaration. Definition is not required
 struct Unit;
 
 ppVector + <unit: Unit*;>;
diff --color -ru stages/stage1/ppp/include/simulation.h stages/stage2/ppp/include/simulation.h
--- stages/stage1/ppp/include/simulation.h	2026-04-10 17:26:12
+++ stages/stage2/ppp/include/simulation.h	2026-04-13 16:04:04
@@ -3,9 +3,11 @@
 
 #include "tribe.h"
 
+// simulation.h - represents the entire simulation state(opaque pointer)
 typedef struct Simulation Simulation;
 
 Simulation* simulation_create(int unit_count, int steps);
+// generate and add units to tribes
 void simulation_add_units(Simulation* sim);
 void simulation_run(Simulation* sim);
 void simulation_destroy(Simulation* sim);
Only in stages/stage2/ppp/include: simulation_context.h
diff --color -ru stages/stage1/ppp/include/tribe.h stages/stage2/ppp/include/tribe.h
--- stages/stage1/ppp/include/tribe.h	2026-04-10 17:26:12
+++ stages/stage2/ppp/include/tribe.h	2026-04-13 16:00:27
@@ -1,14 +1,19 @@
 #ifndef __tribe__
 #define __tribe__
 
+#include "simulation_context.h"
 #include "unit.h"
 #include "container.h"
 
+typedef struct SimulationContext SimulationContext;
+
+// tribe.h - a tribe is like a collection of units with common resources(opaque pointer)
 typedef struct Tribe Tribe;
 
 Tribe* tribe_create(int unit_count);
 void tribe_add(Tribe* tribe, Unit* unit);
-void tribe_act_all(Tribe* tribe);
+void tribe_act_all(Tribe* tribe, SimulationContext* context);
+Unit* get_random_alive_unit(Tribe* tribe);
 void tribe_destroy(Tribe* tribe);
 
 #endif // __tribe__
diff --color -ru stages/stage1/ppp/include/unit.h stages/stage2/ppp/include/unit.h
--- stages/stage1/ppp/include/unit.h	2026-04-10 17:03:09
+++ stages/stage2/ppp/include/unit.h	2026-04-13 16:04:28
@@ -1,16 +1,18 @@
 #ifndef __unit__
 #define __unit__
 
-#include "worker.h"
-#include "warrior.h"
+typedef struct SimulationContext SimulationContext;
 
+// unit.h - generalization representing any unit in the simulation
 typedef struct Unit {
     int id;
+    int health;
 } <> Unit;
 
-void unit_act<Unit *unit>();
-
-Unit + <worker: Worker;>;
-Unit + <warrior: Warrior;>;
+// This method is called when it is the unit's turn in simulation step.
+void unit_act<Unit *unit>(SimulationContext* context);
+int is_alive(Unit* unit);
+void take_damage(Unit* unit, int damage);
+int get_health(Unit* unit);
 
 #endif // __unit__
diff --color -ru stages/stage1/ppp/include/warrior.h stages/stage2/ppp/include/warrior.h
--- stages/stage1/ppp/include/warrior.h	2026-04-10 17:26:12
+++ stages/stage2/ppp/include/warrior.h	2026-04-13 16:07:11
@@ -1,12 +1,23 @@
 #ifndef __warrior__
 #define __warrior__
 
-typedef struct Unit Unit;
+#include "unit.h"
+#include "worker.h"
 
+// warrior.h - specialization of Unit
 typedef struct Warrior {
     int id;
+    int health;
+    int damage;
 } Warrior;
 
+Unit + <warrior: Warrior;>;
+
 Unit* warrior_create(int id);
+// multimethod to attack warrior. Damage is halved due to armor
+// damage * 0.5 is an integer truncation
+void warrior_attack<Unit.warrior* attacker, Unit.warrior* target>();
+// multimethod to attack worker. Full damage
+void warrior_attack<Unit.warrior* attacker, Unit.worker* target>();
 
 #endif // __warrior__
diff --color -ru stages/stage1/ppp/include/worker.h stages/stage2/ppp/include/worker.h
--- stages/stage1/ppp/include/worker.h	2026-04-10 17:26:12
+++ stages/stage2/ppp/include/worker.h	2026-04-13 16:03:05
@@ -1,11 +1,15 @@
 #ifndef __worker__
 #define __worker__
 
-typedef struct Unit Unit;
+#include "unit.h"
 
+// worker.h - specialization of Unit
 typedef struct Worker {
     int id;
+    int health;
 } Worker;
+
+Unit + <worker: Worker;>;
 
 Unit* worker_create(int id);
 
diff --color -ru stages/stage1/ppp/src/simulation.c stages/stage2/ppp/src/simulation.c
--- stages/stage1/ppp/src/simulation.c	2026-04-10 17:26:12
+++ stages/stage2/ppp/src/simulation.c	2026-04-13 16:04:48
@@ -1,18 +1,22 @@
 #include "simulation.h"
+#include "tribe.h"
 #include "warrior.h"
 #include "worker.h"
 #include <stdlib.h>
 
 struct Simulation {
-    Tribe* tribe;
+    Tribe* tribe1;
+    Tribe* tribe2;
     int steps;
     int unit_count;
 };
 
 Simulation* simulation_create(int unit_count, int steps) {
     Simulation* sim = malloc(sizeof(Simulation));
-    Tribe* tribe = tribe_create(unit_count);
-    sim->tribe = tribe;
+    Tribe* tribe1 = tribe_create(unit_count);
+    Tribe* tribe2 = tribe_create(unit_count);
+    sim->tribe1 = tribe1;
+    sim->tribe2 = tribe2;
     sim->steps = steps;
     sim->unit_count = unit_count;
     return sim;
@@ -21,13 +25,18 @@
 void simulation_add_units(Simulation* sim) {
     for(int i = 0; i < sim->unit_count; ++i) {
         int rand_unit = rand() % 2;
-        if(rand_unit) {
-            Unit* u = worker_create(i);
-            tribe_add(sim->tribe, u);
+        // The same type of unit is added to both tribes at once
+        if(rand_unit == 1) {
+            Unit* u1 = worker_create(i);
+            Unit* u2 = worker_create(i+sim->unit_count);
+            tribe_add(sim->tribe1, u1);
+            tribe_add(sim->tribe2, u2);
         }
         else {
-            Unit* u = warrior_create(i);
-            tribe_add(sim->tribe, u);
+            Unit* u1 = warrior_create(i);
+            Unit* u2 = warrior_create(i+sim->unit_count);
+            tribe_add(sim->tribe1, u1);
+            tribe_add(sim->tribe2, u2);
         }
     }
 }
@@ -35,10 +44,20 @@
 void simulation_run(Simulation* sim) {
     for (int step = 0; step < sim->steps; ++step) {
         printf("=== Step %d ===\n", step);
-        tribe_act_all(sim->tribe);
+
+        SimulationContext contextTribe1;
+        contextTribe1.own_tribe = sim->tribe1;
+        contextTribe1.enemy_tribe = sim->tribe2;
+        SimulationContext contextTribe2;
+        contextTribe2.own_tribe = sim->tribe2;
+        contextTribe2.enemy_tribe = sim->tribe1;
+
+        tribe_act_all(sim->tribe1, &contextTribe1);
+        tribe_act_all(sim->tribe2, &contextTribe2);
     }
 }
 
 void simulation_destroy(Simulation* sim) {
-    tribe_destroy(sim->tribe);
+    tribe_destroy(sim->tribe1);
+    tribe_destroy(sim->tribe2);
 }
\ No newline at end of file
diff --color -ru stages/stage1/ppp/src/tribe.c stages/stage2/ppp/src/tribe.c
--- stages/stage1/ppp/src/tribe.c	2026-04-10 17:26:12
+++ stages/stage2/ppp/src/tribe.c	2026-04-13 16:05:57
@@ -20,12 +20,41 @@
     t->unit_count++;
 }
 
-void tribe_act_all(Tribe* tribe) {
+void tribe_act_all(Tribe* tribe, SimulationContext* context) {
     for (int i = 0; i < tribe->unit_count; ++i) {
         Unit* u;
         ppVector_GET_VAL_INDEX(u, tribe->units, i);
-        unit_act<u>();
+        if(!is_alive(u)) continue;
+        unit_act<u>(context);
     }
+}
+
+Unit* get_random_alive_unit(Tribe* tribe) {
+    // Two passes: first we count the live ones, then we go to the desired one.
+    // Does not require an additional buffer.
+    int alive_count = 0;
+    for(int i = 0; i < tribe->unit_count; ++i) {
+        Unit* u;
+        ppVector_GET_VAL_INDEX(u, tribe->units, i);
+        if(is_alive(u)) {
+            alive_count++;
+        }
+    }
+    if(alive_count == 0) return NULL;
+
+    int target = rand() % alive_count;
+    for(int i = 0; i < tribe->unit_count; ++i) {
+        Unit* u;
+        ppVector_GET_VAL_INDEX(u, tribe->units, i);
+        if(!is_alive(u)) {
+            continue;
+        }
+        if(target == 0) {
+            return u;
+        }
+        target--;
+    }
+    return NULL;
 }
 
 void tribe_destroy(Tribe* tribe) {
diff --color -ru stages/stage1/ppp/src/unit.c stages/stage2/ppp/src/unit.c
--- stages/stage1/ppp/src/unit.c	2026-04-10 17:26:12
+++ stages/stage2/ppp/src/unit.c	2026-04-13 15:03:22
@@ -2,6 +2,19 @@
 
 #include "unit.h"
 
-void unit_act<Unit *unit>() {
+void unit_act<Unit *unit>(SimulationContext* context) {
     // overridden by specializations
+}
+
+int is_alive(Unit* unit) {
+    return (unit->health > 0);
+}
+
+void take_damage(Unit* unit, int damage) {
+    unit->health -= damage;
+    if(unit->health < 0) unit->health = 0;
+}
+
+int get_health(Unit* unit) {
+    return unit->health;
 }
\ No newline at end of file
diff --color -ru stages/stage1/ppp/src/warrior.c stages/stage2/ppp/src/warrior.c
--- stages/stage1/ppp/src/warrior.c	2026-04-10 17:26:12
+++ stages/stage2/ppp/src/warrior.c	2026-04-13 15:03:25
@@ -1,12 +1,33 @@
 #include <stdio.h>
-#include "unit.h"
+#include "warrior.h"
+#include "tribe.h"
 
 Unit* warrior_create(int id) {
-    Unit* u = create_spec(Unit.warrior);
+    struct Unit.warrior* u = create_spec(Unit.warrior);
     u->id = id;
-    return u;
+    u->health = 100;
+    u->@damage = 35;
+    return (Unit*)u;
 }
 
-void unit_act<Unit.warrior* unit>() {
-    printf("Warrior %d is attacking\n", unit->id);
-}
+void warrior_attack<Unit* attacker, Unit* target>() {} //= 0;
+
+void unit_act<Unit.warrior* unit>(SimulationContext* context) {
+    Unit* target = get_random_alive_unit(context->enemy_tribe);
+    if(target == NULL) {
+        printf("Warrior %d didn't find enemy to attack\n", unit->id);
+        return;
+    }
+    warrior_attack<(Unit*)unit, target>();
+}
+
+void warrior_attack<Unit.warrior* attacker, Unit.warrior* target>()
+{
+    take_damage((Unit*)target, attacker->@damage * 0.5);
+    printf("Warrior %d is attacking warrior %d, target health %d\n", attacker->id, target->id, target->health);
+}
+
+void warrior_attack<Unit.warrior* attacker, Unit.worker* target>() {
+    take_damage((Unit*)target, attacker->@damage);
+    printf("Warrior %d is attacking worker %d, target health %d\n", attacker->id, target->id, target->health);
+}
\ No newline at end of file
diff --color -ru stages/stage1/ppp/src/worker.c stages/stage2/ppp/src/worker.c
--- stages/stage1/ppp/src/worker.c	2026-04-10 17:26:12
+++ stages/stage2/ppp/src/worker.c	2026-04-13 15:03:31
@@ -1,13 +1,14 @@
 #include <stdio.h>
-#include "unit.h"
+#include "worker.h"
 
 Unit* worker_create(int id) {
-    Unit* u = create_spec(Unit.worker);
+    struct Unit.worker* u = create_spec(Unit.worker);
     u->id = id;
-    return u;
+    u->health = 100;
+    return (Unit*)u;
 }
 
 
-void unit_act<Unit.worker* unit>() {
+void unit_act<Unit.worker* unit>(SimulationContext* context) {
     printf("Worker %d is working\n", unit->id);
 }

```