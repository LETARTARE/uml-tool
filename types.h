#pragma once

#include <QHash>
#include <QMap>
#include <QSet>
#include <QStringList>
#include <QMultiHash>
#include <memory>

using ErrorList = QStringList;
using SharedErrorList = std::shared_ptr<ErrorList>;

namespace entity {
    class Field;
    using SharedField = std::shared_ptr<Field>;
    using Fields      = QHash<QString, SharedField>;
    using FieldsList  = QList<SharedField>;

    enum FieldKeyword : int;
    using FieldKeywords     = QSet<FieldKeyword>;
    using FieldKeywordsList = QList<FieldKeyword>;

    class ClassMethod;
    using SharedMethod = std::shared_ptr<ClassMethod>;
    using Methods      = QMultiHash<QString, SharedMethod>;
    using MethodsList  = QList<SharedMethod>;

    class TemplateClassMethod;
    using SharedTemplateClassMethod = std::shared_ptr<TemplateClassMethod>;

    enum  LhsIdentificator : int;
    using LhsIdentificators     = QSet<LhsIdentificator>;
    using LhsIdentificatorsList = QList<LhsIdentificator>;

    class Type;
    using SharedType = std::shared_ptr<Type>;
    using Types      = QHash<QString, SharedType>;
    using TypesList  = QList<SharedType>;

    class Class;
    using SharedClass = std::shared_ptr<Class>;
    using Classes     = QHash<QString, SharedClass>;
    using ClassesList = QList<SharedClass>;

    class TemplateClass;
    using SharedTemplateClass = std::shared_ptr<TemplateClass>;

    class Template;
    using SharedTemplate = std::shared_ptr<Template>;

    class Union;
    using SharedUnion = std::shared_ptr<Union>;
    using Unions      = QHash<QString, SharedUnion>;
    using UnionsList  = QList<SharedUnion>;

    class Enum;
    using SharedEnum = std::shared_ptr<Enum>;
    using Enums      = QHash<QString, SharedEnum>;
    using EnumsList  = QList<SharedEnum>;

    enum Section : int;
    using Parent      = std::pair<QString, Section>;
    using Parents     = QHash<QString, Parent>; // id : {id, section}
    using ParentsList = QList<Parent>;

    class ExtendedType;
    using TemplateParameter      = QPair<QString, QString>; // (type id, default type id)
    using TemplateParameters     = QHash<QString, TemplateParameter>;
    using TemplateParametersList = QList<TemplateParameter>;
    using SharedExtendedType     = std::shared_ptr<ExtendedType>;
    using ExtendedTypes          = QHash<QString, SharedExtendedType>;
    using ExtendedTypesList      = QList<SharedExtendedType>;
    using ExtendedTypesIdList    = QStringList;

    class Scope;
    using SharedScope = std::shared_ptr<Scope>;
    using Scopes      = QHash<QString, SharedScope>;
    using ScopesList  = QList<SharedScope>;
}

namespace relationship {
    class Node;
    using SharedNode = std::shared_ptr<Node>;

    class Relation;
    using SharedRelation = std::shared_ptr<Relation>;
    using Relations = QHash<QString, SharedRelation>;
    using RelationsList = QList<SharedRelation>;
}

namespace db {
    class Database;
    class ProjectDatabase;
    using SharedDatabase = std::shared_ptr<Database>;
    using SharedProjectDatabase = std::shared_ptr<ProjectDatabase>;
}

namespace translator {
    class ProjectTranslator;
    using SharedTranslator = std::shared_ptr<ProjectTranslator>;
}

namespace generator {
    class VirtualFileSystemAbstractItem;
    using SharedVirtualSystemBasicItem = std::shared_ptr<VirtualFileSystemAbstractItem>;
    using VirtualFiles = QHash<QString, SharedVirtualSystemBasicItem>;

    class VirtualFile;
    using SharedVirtualFile = std::shared_ptr<VirtualFile>;

    class VirtualDirectory;
    using SharedVirtualDirectory = std::shared_ptr<VirtualDirectory>;

    class AbstractProjectGenerator;
    using SharedGenerator = std::shared_ptr<AbstractProjectGenerator>;

    using ProfileVariables = QMap<QString,  // name
                                  QString>; // value
}

namespace project {
    class Project;
    using SharedProject = std::shared_ptr<Project>;
    using Projects = QHash<QString, SharedProject>;
    using ProjectsList = QList<SharedProject>;
}
