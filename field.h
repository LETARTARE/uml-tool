#pragma once

#include <QString>

namespace entity {

    class ExtendedType;
    enum Section : int;

    class Field
    {
    public:
        Field();
        Field(const QString &name, ExtendedType *type);

        ExtendedType *type() const;
        void setType(ExtendedType *type);

        QString name() const;
        void setName(const QString &name);

        Section section() const;
        void setSection(Section section);

    private:
        ExtendedType *m_Type;
        Section       m_Section;
        QString       m_Name;
    };

} // namespace entity
