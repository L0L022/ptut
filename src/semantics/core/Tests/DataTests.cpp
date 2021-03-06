#include <semantics/core/Tests/DataTests.hpp>

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <iostream>

namespace semantics {
namespace core {

DataTests::DataTests(QObject *parent) : QObject(parent) {}

void DataTests::initTestCase() {}

void DataTests::init() {}

void DataTests::cleanup() {}

void DataTests::toAndFromMap() {
  std::unique_ptr<Form> f_origin = create_form();
  std::unique_ptr<Form> f_copy(Form::fromMap(f_origin->toMap()));
  QCOMPARE(*f_origin, *f_copy);
}

std::unique_ptr<Form> DataTests::create_form() {
  ClosedQuestion::Choices::SharedDataPtr choicesSharedData =
      std::make_shared<ClosedQuestion::Choices::SharedData>();
  Form::Questions::SharedDataPtr questionsSharedData =
      std::make_shared<Form::Questions::SharedData>();
  Form::Subjects::SharedDataPtr subjectsSharedData =
      std::make_shared<Form::Subjects::SharedData>();

  Form::Questions questions;

  for (size_t i = 0; i < 5; ++i) {
    auto id = questionsSharedData->takeId();
    questions.insert(std::make_unique<OpenedQuestion>(id, QString("Opened question n %1").arg(id), 10));
  }

  for (size_t i = 0; i < 3; ++i) {
    ClosedQuestion::Choices choices;
    for (size_t i = 0; i < 5; ++i) {
      auto c = std::make_unique<Choice>(choicesSharedData->takeId());
      c->setLabel(QString("Choice %1").arg(c->id()));
      choices.insert(std::move(c));
    }
    auto id = questionsSharedData->takeId();
      questions.insert(std::make_unique<ClosedQuestion>(id,
                                                        ClosedQuestion::Unique,
                                                        choices,
                                                        QString("Unique closed question n %1").arg(id)));

        questions.insert(std::make_unique<ClosedQuestion>(id,
                                                          ClosedQuestion::Multiple,
                                                          choices,
                                                          QString("Multiple closed question n %1").arg(id)));
  }

  return std::make_unique<Form>(1, questions, subjectsSharedData, "Name", "Description");
}

}
}

QTEST_MAIN(semantics::core::DataTests)
