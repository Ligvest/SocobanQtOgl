#include "selectlevelmenu.hpp"
#include "map.hpp"

SelectLevelMenu::SelectLevelMenu(const std::vector<Level>* pVecLevels) {
    iCurItem_ = 0;
    iMinDisplayedItem_ = 0;
    iMaxDisplayedItem_ = 5;
    pVecLevels_ = pVecLevels;
    updateRangeToDisplay();
}

int SelectLevelMenu::curItem() const { return iCurItem_; }

Level SelectLevelMenu::curLevel() const { return (*pVecLevels_)[curItem()]; }

void SelectLevelMenu::nextItem() {
    if (iCurItem_ != (static_cast<int>(pVecLevels_->size() - 1))) {
        if (iCurItem_ >= (iMaxDisplayedItem_ - 1)) {
            ++iMaxDisplayedItem_;
            ++iMinDisplayedItem_;
            updateRangeToDisplay();
        }
        ++iCurItem_;
    }
}

void SelectLevelMenu::prevItem() {
    if (iCurItem_ > 0) {
        if (iCurItem_ <= iMinDisplayedItem_) {
            --iMaxDisplayedItem_;
            --iMinDisplayedItem_;
            updateRangeToDisplay();
        }
        --iCurItem_;
    }
}

void SelectLevelMenu::updateRangeToDisplay() {
    listRangeToDisplay_.clear();
    for (int iDisplayItemNumber = iMinDisplayedItem_;
         iDisplayItemNumber < iMaxDisplayedItem_; ++iDisplayItemNumber) {
        std::string sLevelName = (*pVecLevels_)[iDisplayItemNumber].name();
        listRangeToDisplay_.push_back(
            std::make_pair(iDisplayItemNumber, sLevelName));
    }
}

std::list<std::pair<int, std::string>> SelectLevelMenu::rangeToDisplay() const {
    return listRangeToDisplay_;
}
