#include <string>
#include <ros/ros.h>
#include <vector>
#include "armor_msgs/ArmorDirective.h"
#include "armor_msgs/ArmorDirectiveRequest.h"
#include "armor_msgs/ArmorDirectiveList.h"
#include "rosplan_knowledge_msgs/KnowledgeItem.h"

#ifndef ROSPLAN_KNOWLEDGE_BASE_ARMORMANAGER_H
#define ROSPLAN_KNOWLEDGE_BASE_ARMORMANAGER_H

namespace KCL_rosplan {

    class ArmorManager {

    private:
        std::string refName;
        ros::NodeHandlePtr nh;
        ros::ServiceClient armorClient;
        ros::ServiceClient armorClientSerial;
        armor_msgs::ArmorDirectiveRequest msgTemplate;
        int maxId = 0;
        std::vector<std::string> argsProperties = {"has_first_arg", "has_second_arg", "has_third_arg"};

        void setMsgDirective(armor_msgs::ArmorDirectiveRequest& msg, std::string command,
                             std::string primarySpec, std::string secondarySpec);

        armor_msgs::ArmorDirectiveRequest newMessage(std::string command,
                                                     std::string primarySpec,
                                                     std::string secondarySpec,
                                                     std::vector<std::string> args);

        armor_msgs::ArmorDirectiveRequest newMessage(std::string command,
                                                     std::string primarySpec,
                                                     std::string secondarySpec);

        std::string addPredicate(std::string predicateName, rosplan_knowledge_msgs::KnowledgeItem msg, bool normative);

        bool applyChanges();

    public:
        ArmorManager(std::string refName, ros::NodeHandlePtr nh);
        bool pollDomainOntology();
        std::string getRefName();
        std::string addInstance(std::string type, std::string name);
        std::string addFact(std::string predicateName, rosplan_knowledge_msgs::KnowledgeItem msg);
        std::string addNorm(std::string predicateName, rosplan_knowledge_msgs::KnowledgeItem msg);
        bool removeEntity(std::string entityName);
        bool clearClass(std::string className);
        std::vector<rosplan_knowledge_msgs::KnowledgeItem> getCurrentGoals();

    };

}

#endif //ROSPLAN_KNOWLEDGE_BASE_ARMORMANAGER_H
