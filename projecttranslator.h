#pragma once

#include "types.h"

namespace translator {

    struct Code;

    class ProjectTranslator
    {
    public:
        enum TranslatorOption {
            NoOptions       = 0x0,
            WithNamespace   = 0x1,
            WithAlias       = 0x2,
            GenerateNumbers = 0x4,
        };
        Q_DECLARE_FLAGS(TranslatorOptions, TranslatorOption)

        ProjectTranslator();
        ProjectTranslator(const db::SharedDatabase &globalDb,
                          const db::SharedDatabase &projectDb);

        db::SharedDatabase globalDatabase() const;
        void setGlobalDatabase(const db::SharedDatabase &globalDatabase);

        db::SharedDatabase projectDatabase() const;
        void setProjectDatabase(const db::SharedDatabase &projectDatabase);

        Code translate(const entity::SharedType &type,
                       const TranslatorOptions &options = WithNamespace,
                       const db::SharedDatabase &localeDatabase = nullptr,
                       const db::SharedDatabase &classDatabase = nullptr) const;

        Code translate(const entity::SharedExtendedType &extType,
                       const TranslatorOptions &options = WithNamespace,
                       const db::SharedDatabase &localeDatabase = nullptr,
                       const db::SharedDatabase &classDatabase = nullptr) const;
        Code translate(const entity::SharedField &field,
                       const TranslatorOptions &options = WithNamespace,
                       const db::SharedDatabase &localeDatabase = nullptr,
                       const db::SharedDatabase &classDatabase = nullptr) const;
        Code translate(const entity::SharedEnum &_enum,
                       const TranslatorOptions &options = NoOptions,
                       const db::SharedDatabase &localeDatabase = nullptr,
                       const db::SharedDatabase &classDatabase = nullptr) const;
        Code translate(const entity::SharedMethod &method,
                       const TranslatorOptions &options = NoOptions,
                       const db::SharedDatabase &localeDatabase = nullptr,
                       const db::SharedDatabase &classDatabase = nullptr) const;
        Code translate(const entity::SharedUnion &_union,
                       const TranslatorOptions &options = NoOptions,
                       const db::SharedDatabase &localeDatabase = nullptr,
                       const db::SharedDatabase &classDatabase = nullptr) const;
        Code translate(const entity::SharedClass &_class,
                       const TranslatorOptions &options = NoOptions,
                       const db::SharedDatabase &localeDatabase = nullptr,
                       const db::SharedDatabase &classDatabase = nullptr) const;
        Code translate(const entity::SharedTemplateClass &_class,
                       const TranslatorOptions &options = NoOptions,
                       const db::SharedDatabase &localeDatabase = nullptr,
                       const db::SharedDatabase &classDatabase = nullptr) const;

        Code generateClassMethodsImpl(const entity::SharedClass &_class,
                                      const db::SharedDatabase &localeDatabase = nullptr) const;
        Code generateClassMethodsImpl(const entity::SharedTemplateClass &_class) const;

    private:
        void checkDb() const;
        void makeCallbacks();
        QString generateCodeForExtTypeOrType(const QString &id, const TranslatorOptions &options,
                                             const db::SharedDatabase &localeDatabase = nullptr,
                                             const db::SharedDatabase &classDatabase = nullptr) const;
        void generateClassSection(const entity::SharedClass &_class,
                                  const db::SharedDatabase &localeDatabase,
                                  entity::Section section, QString &out) const;
        void generateFieldsAndMethods(const entity::SharedClass &_class,
                                      const db::SharedDatabase &localeDatabase,
                                      const QString &indent,
                                      entity::Section section,
                                      QString &out) const;
        void generateTemplatePart(QString &result, const entity::SharedTemplate &t, bool withDefaultTypes = true) const;
        bool toHeader(const entity::SharedMethod &m,
                      const db::SharedDatabase &classDatabase = nullptr) const;

        db::SharedDatabase m_GlobalDatabase;
        db::SharedDatabase m_ProjectDatabase;
    };

    Q_DECLARE_OPERATORS_FOR_FLAGS(ProjectTranslator::TranslatorOptions)

} // namespace translator
