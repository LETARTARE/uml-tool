#pragma once

#include "types.h"
#include "database.h"

namespace db {

    class ProjectDatabase : public Database
    {
    public:
        ProjectDatabase(const QString &name = "", const QString &path = "");

        relationship::SharedRelation getRelation(const QString &id) const;
        void addRelation(const relationship::SharedRelation &relation);
        bool containsRelation(const QString &id) const;
        void removeRelation(const QString &id);
        relationship::RelationsList relations() const;

        db::SharedDatabase globalDatabase() const;
        void setGlobalDatabase(const db::SharedDatabase &globalDatabase);

        void clear() override;

        QJsonObject toJson() const override;
        void fromJson(const QJsonObject &src, QStringList &errorList) override;

    private:
        relationship::Relations m_Relations;
        db::SharedDatabase m_GlobalDatabase;
    };

} // namespace db

