//
// Autorzy:
// Michał Rokita, Adamski Maciej
//

#ifndef ZTMAPI_CORE_SECTION_H
#define ZTMAPI_CORE_SECTION_H

#include <iomanip>
#include <iostream>
#include <utility>
#include <memory>
#include "ScheduleManager.h"
#include <boost/regex/icu.hpp>

class ScheduleManager;

class InvalidSectionException : public std::exception {
public:
    explicit InvalidSectionException(std::string sectionKey) : sectionKey(std::move(sectionKey)){

    }
    virtual const char* what() const throw() {
        return sectionKey.c_str();
    }
    const std::string sectionKey;
};

class CouldNotParseLineException : public std::exception {
public:
    explicit CouldNotParseLineException(std::string line) : line(std::move(line)){

    }
    virtual const char* what() const throw() {
        return line.c_str();
    }
    const std::string line;
};


class Section : public std::enable_shared_from_this<Section> {
public:
    explicit Section(ScheduleManager* manager) : manager(manager){
    }

    void processLine(const std::string& line);

	/**
	 * Zamyka daną sekcję.
	 * @param sectionKey Klucz zamykanej sekcji
	 */
    void closeSection(const std::string& sectionKey){
        if(!currentSubSection){
            throw std::runtime_error("Couldn't close " + sectionKey + " - not in the tree");
        }
        if(currentSubSectionID == sectionKey){
            currentSubSection.reset();
            currentSubSectionID = "";
        } else {
            return currentSubSection->closeSection(sectionKey);
        }
    }

	/**
	 * Otwiera daną sekcję
	 * @param sectionKey Klucz otwieranej sekcji
	 */
    void openSection(const std::string& sectionKey);


    void setParent(std::shared_ptr<Section> section) {
        _parentSection = section;
    }

	/**
	 * Ustawia rodzica dla podsekcji.
	 * @param subSection Dla jakiej sekcji podrzędnej ma być ustawione
	 */
    virtual void applyToSubSection(std::shared_ptr<Section> subSection){
        subSection->setParent(shared_from_this());
    }

protected:

    ScheduleManager* manager;
    std::shared_ptr<Section>  _parentSection;
	
	/**
	 * Parsowanie pojedynczej linii pliku
	 * Funkcja wywoływana dla każdej linii parsowanego pliku. Metoda wirtualna, nadpisywana przez każdą sekcję
	 * @param Linia pliku 
	 */
    virtual void _processLine(const std::string&) = 0;
private:
    std::shared_ptr<Section> currentSubSection;
    std::string currentSubSectionID; /**< Aktualnie parsowana sekcja podrzędna. */
};

template <class ParentSection>
class SubSection : public Section {
    using Section::Section;
public:
    virtual std::shared_ptr<ParentSection> getParent(){
        return std::dynamic_pointer_cast<ParentSection>(_parentSection);
    }
};


class MainSection : public Section {
    using Section::Section;
protected:
    void _processLine(const std::string& line) override {

    }
};


#endif //ZTMAPI_CORE_SECTION_H
