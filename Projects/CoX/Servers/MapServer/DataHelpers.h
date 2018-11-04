/*
 * SEGS - Super Entity Game Server
 * http://www.segs.io/
 * Copyright (c) 2006 - 2018 SEGS Team (see AUTHORS.md)
 * This software is licensed under the terms of the 3-clause BSD License. See LICENSE.md for details.
 */

#pragma once
#include "Messages/Map/MessageChannels.h"
#include "Common/GameData/Contact.h"
#include "Common/GameData/Task.h"
#include "glm/vec3.hpp"
#include <vector>

class QString;
class Entity;
class Character;
struct Friend;
struct FriendsList;
struct MapClientSession;
struct CharacterPowerSet;
struct CharacterPower;
struct PowerStance;
class GameDataStore;
class TradeMember;
struct ContactEntry;
enum FloatingInfoStyle : int;
enum class ClientStates : uint8_t;

/*
 * This file is intended to hold helper functions for methods
 * requiring access to MapClientSession or MapInstance
 */
Entity * getEntity(MapClientSession *src, const QString &name);
Entity * getEntity(MapClientSession *src, uint32_t idx);
Entity * getEntityByDBID(class MapInstance *mi,uint32_t idx);
void    sendServerMOTD(MapClientSession *sess);
void    positionTest(MapClientSession *tgt);
bool    isFriendOnline(Entity &sess, uint32_t db_id);
void    setInterpolationSettings(MapClientSession *sess, const bool active, const uint8_t level, const uint8_t bits);
QString createMapMenu();


/*
 * sendEmail Wrappers for providing access to Email Database
 */
void readEmailMessage(MapClientSession& sess, const uint32_t email_id);
void sendEmail(MapClientSession& sess, QString recipient_name, QString subject, QString message);
void deleteEmailHeaders(MapClientSession& sess, const uint32_t email_id);

// to get the current time since whatever they set as their beginning
uint32_t getCurrentTime();


/*
 * SendUpdate Wrappers
 */
void sendInfoMessage(MessageChannel ch, const QString &msg, MapClientSession &tgt);
void sendTimeStateLog(MapClientSession &sess, uint32_t control_log);
void sendTimeUpdate(MapClientSession &sess, int32_t sec_since_jan_1_2000);
void sendClientState(MapClientSession &sess, ClientStates client_state);
void showMapXferList(MapClientSession &sess, bool has_location, glm::vec3 &location, QString &name);
void sendFloatingInfo(MapClientSession &sess, QString &msg, FloatingInfoStyle style, float delay);
void sendFloatingNumbers(MapClientSession &sess, uint32_t tgt_idx, int32_t amount);
void sendLevelUp(MapClientSession &sess);
void sendEnhanceCombineResponse(MapClientSession &sess, bool success, bool destroy);
void sendChangeTitle(MapClientSession &sess, bool select_origin);
void sendTrayAdd(MapClientSession &sess, uint32_t pset_idx, uint32_t pow_idx);
void sendFriendsListUpdate(MapClientSession &sess, const FriendsList &friends_list);
void sendSidekickOffer(MapClientSession &sess, uint32_t src_db_id);
void sendTeamLooking(MapClientSession &sess);
void sendTeamOffer(MapClientSession &src, MapClientSession &tgt);
void sendFaceEntity(MapClientSession &src, int32_t tgt_idx);
void sendFaceLocation(MapClientSession &sess, glm::vec3 &loc);
void sendDoorMessage(MapClientSession &sess, uint32_t delay_status, QString &msg);
void sendBrowser(MapClientSession &sess, QString &content);
void sendTradeOffer(MapClientSession &tgt, const QString &name);
void sendTradeInit(MapClientSession &src, MapClientSession &tgt);
void sendTradeCancel(MapClientSession &sess, const QString &msg);
void sendTradeUpdate(MapClientSession &src, MapClientSession &tgt, const TradeMember& trade_src, const TradeMember& trade_tgt);
void sendTradeSuccess(MapClientSession &src, MapClientSession &tgt);
void sendContactDialog(MapClientSession &sess, QString msg_body, std::vector<ContactEntry> active_contacts);
void sendContactDialogYesNoOk(MapClientSession &sess, QString msg_body, bool has_yesno);
void sendContactDialogClose(MapClientSession &sess);
void updateContactStatusList(MapClientSession &sess, const Contact &contact_to_update);
void sendContactStatusList(MapClientSession &sess);
void sendWaypoint(MapClientSession &sess, int point_idx, glm::vec3 &location);
void sendStance(MapClientSession &sess, PowerStance &stance);
void sendDeadNoGurney(MapClientSession &sess);
void sendDoorAnimStart(MapClientSession &sess, glm::vec3 &entry_pos, glm::vec3 &target_pos, bool has_anims, QString &seq_state);
void sendDoorAnimExit(MapClientSession &sess, bool force_move);

/*
 * usePower and increaseLevel here to provide access to
 * both Entity and sendInfoMessage
 */
void usePower(Entity &ent, uint32_t pset_idx, uint32_t pow_idx, int32_t tgt_idx, int32_t tgt_id);
void increaseLevel(Entity &ent);

/*
 * Lua Functions
 */
void addNpc(MapClientSession &sess, QString &npc_name, glm::vec3 &loc, int variation, QString &name);
void addNpcWithOrientation(MapClientSession &sess, QString &name, glm::vec3 &loc, int variation, glm::vec3 &ori);
void giveEnhancement(MapClientSession &sess, QString &name, int level);
void giveDebt(MapClientSession &sess, int debt);
void giveEnd(MapClientSession &sess, float end);
void giveHp(MapClientSession &sess, float hp);
void giveInf(MapClientSession &sess, int inf);
void giveInsp(MapClientSession &sess, QString &name);
void giveXp(MapClientSession &sess, int xp);
void addListOfTasks(MapClientSession *cl, vTaskList task_list);
void sendUpdateTaskStatusList(MapClientSession &src, Task task);
void selectTask(MapClientSession &src, Task task);
void sendTaskStatusList(MapClientSession &src);
void updateTaskDetail(MapClientSession &src, Task task);
void removeTask(MapClientSession &src, Task task);
void train (MapClientSession &sess);
void setTitle (MapClientSession &sess, QString title);
void showMapMenu(MapClientSession &sess);
