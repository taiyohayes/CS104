#include "labellist.h"
#include <cassert>

// Complete - Do not alter
LabelList::MsgNode::MsgNode(const MsgType& msg)
    : msg_(msg)
{
    // Every message is part of the "all" (index 0) label
    labelled_.push_back(1);
    next_.push_back(nullptr);
    prev_.push_back(nullptr);
}


// Complete - Do not alter
// invalid message token
LabelList::MsgToken::MsgToken()
 : node_(nullptr), list_(nullptr)
{
}

// To be completed - must adhere to any requirements in the .h file
LabelList::MsgToken::MsgToken(MsgNode* node, LabelList* list)
// Add any initializers here
 : node_(node), list_(list)
{    
}

// To be completed - must adhere to any requirements in the .h file
bool LabelList::MsgToken::operator==(const MsgToken& rhs) const
{
    return rhs.node_ == this->node_;
}

// Complete - Do not alter
bool LabelList::MsgToken::operator!=(const MsgToken& rhs) const
{
    return !operator==(rhs);
}

// To be completed - must adhere to any requirements in the .h file
LabelList::MsgToken::operator bool() const
{
    return this->isValid();
}

// Complete - Do not alter
bool LabelList::MsgToken::isValid() const
{
    return this->node_ != nullptr;
}

// Complete - Do not alter
LabelList::MsgToken& LabelList::MsgToken::next(const LabelType& label)
{
    size_t index = this->list_->findLabelIndex(label);
    if( false == this->isLabelMember(index) ) 
    {
        throw std::invalid_argument("Node is not part of the given label");
    }
    this->node_ = this->node_->next_[index];

    // Should return reference to self
    return *this;
}

// Complete - Do not alter
LabelList::MsgToken& LabelList::MsgToken::prev(const LabelType& label)
{
    size_t index = this->list_->findLabelIndex(label);
    if( false == this->isLabelMember(index) ) 
    {
        throw std::invalid_argument("Node is not part of the given label");
    }
    this->node_ = this->node_->prev_[index];

    // Should return reference to self
    return *this;
}

// Complete - Do not alter
bool LabelList::MsgToken::isLabelMember(const LabelType& label) const
{
    size_t index = this->list_->findLabelIndex(label);
    return isLabelMember(index);
}

// Complete - Do not alter
bool LabelList::MsgToken::isLabelMember(size_t index) const
{
    return this->isValid() && 
            index != INVALID_LABEL &&
            index < this->node_->labelled_.size() &&
            this->node_->labelled_[index] ;
}

// To be completed - must adhere to any requirements in the .h file
LabelList::MsgType const & LabelList::MsgToken::msg() const
{
    if (false == this->isValid())
    {
        throw std::logic_error("Token references an invalid message");
    }
    MsgType& mesg = this->node_->msg_;
    return mesg;
}
// To be completed - must adhere to any requirements in the .h file
LabelList::MsgType& LabelList::MsgToken::msg() 
{
    if (false == this->isValid())
    {
        throw std::logic_error("Token references an invalid message");
    }
    MsgType& mesg = this->node_->msg_;
    return mesg;

}

// To be completed - must adhere to any requirements in the .h file
std::ostream& operator<<(std::ostream& ostr, const LabelList::MsgToken& token)
{
    if(token.isValid())
    {
        ostr << token.node_->msg_;
    }
    return ostr;
}

// Static constant 
const LabelList::MsgToken LabelList::end_(nullptr, nullptr);

// To be completed - must adhere to any requirements in the .h file
LabelList::LabelList() 
// Add any initializers here
{
    std::string str = "all";
    this->labels_.push_back(str);
    this->heads_.push_back(nullptr);
    this->tails_.push_back(nullptr);
}

// To be completed - must adhere to any requirements in the .h file
LabelList::~LabelList()
{
    this->clear();
}

// To be completed - must adhere to any requirements in the .h file
void LabelList::clear()
{
    MsgNode* deleter = this->heads_[0];
    while (this->heads_[0] != nullptr)
    {
        this->heads_[0] = this->heads_[0]->next_[0];
        delete deleter;
        deleter = this->heads_[0];
    }
    this->labels_.clear();
    this->heads_.clear();
    this->tails_.clear();
    std::string str = "all";
    this->labels_.push_back(str);
    this->heads_.push_back(nullptr);
    this->tails_.push_back(nullptr);
       
}

// To be completed - must adhere to any requirements in the .h file
bool LabelList::empty() const
{
    return this->heads_[0] == nullptr;
}

// Complete
size_t LabelList::size() const
{
    MsgNode* n = this->heads_[0];
    size_t cnt = 0;
    while(n != nullptr){
        cnt++;
        n = n->next_[0];
    }
    return cnt;
}

// To be completed - must adhere to any requirements in the .h file
LabelList::MsgToken LabelList::add(const MsgType& msg)
{
    MsgNode* newNode = new MsgNode(msg);
    if (this->empty() == 1)
    {
        this->heads_[0] = newNode;
        this->tails_[0] = newNode;
        newNode->prev_[0] = nullptr;
        newNode->next_[0] = nullptr;
    }
    else 
    {
        this->tails_[0]->next_[0] = newNode;
        newNode->prev_[0] = this->tails_[0];
        this->tails_[0] = newNode;
        newNode->next_[0] = nullptr;
    }
    MsgToken newToken(newNode, this);
    return newToken;
}


// To be completed - must adhere to any requirements in the .h file
void LabelList::remove(const MsgToken& token)
{
    if(!token.isValid())
    {
        return;
    }
    for (unsigned int i = 0; i < this->labels_.size(); i++)
    {
        if (token.node_->labelled_[i] == 1)
        {
            if (token.node_->prev_[i] == nullptr || token.node_->next_[i] == nullptr)
            {
                if (token.node_->prev_[i] == nullptr && token.node_->next_[i] == nullptr)
                {
                    this->heads_[i] = nullptr;
                    this->tails_[i] = nullptr;
                }
                else if (token.node_->prev_[i] == nullptr)
                {
                    token.node_->next_[i]->prev_[i] = nullptr;
                    this->heads_[i] = token.node_->next_[i];
                }
                else if (token.node_->next_[i] == nullptr)
                {
                    token.node_->prev_[i]->next_[i] = nullptr;
                    this->tails_[i] = token.node_->prev_[i];
                }  
            } 
            else
            {
                token.node_->next_[i]->prev_[i] = token.node_->prev_[i];
                token.node_->prev_[i]->next_[i] = token.node_->next_[i];
            }
        }
    }
    delete token.node_;
}

// To be completed - must adhere to any requirements in the .h file
void LabelList::label(const MsgToken& token, const LabelType& label)
{
    if(!token.isValid())
    {
        throw std::invalid_argument("Bad token in label()");
    }
    size_t index = this->findLabelIndex(label);
    /*if(index >= 0 && token.isLabelMember(index) == 1)
    {
        return;
    }*/
    if (index == INVALID_LABEL)
    {
        this->labels_.push_back(label);
        this->heads_.push_back(token.node_);
        this->tails_.push_back(token.node_);
        size_t old = token.node_->labelled_.size();
        //size_t newIndex = getLabelIndex(label);
        size_t newIndex = this->labels_.size()-1;
        token.node_->labelled_.resize(newIndex+1);
        for (unsigned int i = old; i < newIndex; i++)
        {
            token.node_->labelled_[i] = 0;
        }
        token.node_->labelled_[newIndex] = 1;
        token.node_->prev_.resize(newIndex+1);
        token.node_->next_.resize(newIndex+1);
        token.node_->prev_[newIndex] = nullptr;
        token.node_->next_[newIndex] = nullptr;
    }
    else
    {
        MsgNode* fTracker = token.node_->next_[0];
        MsgNode* bTracker = token.node_->prev_[0];
        if (token.node_->labelled_.size() <= index)
        {
            token.node_->labelled_.resize(index+1);
            token.node_->prev_.resize(index+1);
            token.node_->next_.resize(index+1);
        }
        token.node_->labelled_[index] = 1; 
        while(fTracker != nullptr)
        {
            if (fTracker->labelled_[index] == 1)
            {
                token.node_->next_[index] = fTracker; 
                fTracker->prev_[index] = token.node_;
                break;
            }
            fTracker = fTracker->next_[0];
        }
        if (fTracker == nullptr)
        {
            this->tails_[index] = token.node_;
            token.node_->next_[index] = nullptr;
        }
        while (bTracker != nullptr)
        {
            if (bTracker->labelled_[index] == 1)
            {
                token.node_->prev_[index] = bTracker;
                bTracker->next_[index] = token.node_;
                break;
            }
            bTracker = bTracker->prev_[0];
        }
        if (bTracker == nullptr)
        {
            this->heads_[index] = token.node_;
            token.node_->prev_[index] = nullptr;
        }
    }
}

// To be completed - must adhere to any requirements in the .h file
void LabelList::unlabel(const MsgToken& token, const LabelType& label)
{
    if(!token.isValid())
    {
        throw std::invalid_argument("Bad token in label()");
    }
    size_t index = this->getLabelIndex(label);
    if (token.node_->labelled_[index] == 0)
    {
        return;
    }
    if (index == 0)
    {
    }
    else
    {
        token.node_->labelled_[index] = 0;
        if (token.node_->prev_[index] == nullptr || token.node_->next_[index] == nullptr)
        {
            if (token.node_->prev_[index] == nullptr && token.node_->next_[index] == nullptr)
            {
                this->heads_[index] = nullptr;
                this->tails_[index] = nullptr;
            }
            else if (token.node_->prev_[index] == nullptr)
            {
                this->heads_[index] = token.node_->next_[index];
                token.node_->next_[index]->prev_[index] = nullptr;
            }
            else if (token.node_->next_[index] == nullptr)
            {
                this->tails_[index] = token.node_->prev_[index];
                token.node_->prev_[index]->next_[index] = nullptr;
            }
        }
        else
        {
            token.node_->next_[index]->prev_[index] = token.node_->prev_[index];
            token.node_->prev_[index]->next_[index] = token.node_->next_[index];    
        }
    }
}

// Complete - Do not alter
LabelList::MsgToken LabelList::find(const MsgType& msg, const LabelType& label)
{
    // See if the label exists, will throw if not
    size_t level = this->getLabelIndex(label);
    MsgNode* n = this->heads_[level];
    while(n != nullptr)
    {
        if(n->msg_ == msg)
        {
            return MsgToken(n, this);
        }
        n = n->next_[level];
    }
    return end();
}

// To be completed - must adhere to any requirements in the .h file
LabelList::MsgToken LabelList::find(size_t index, const LabelType& label)
{
    size_t level = this->getLabelIndex(label);
    MsgNode* tracker = this->heads_[level];
    size_t counter = 0;
    while(tracker != nullptr)
    {
        if (counter == index)
        {
            return MsgToken(tracker, this);
        }
        tracker = tracker->next_[level];
        counter++;
    }
    return end();
}

// Complete - Do not alter
LabelList::MsgToken const & LabelList::end() const
{
    return end_;
}

// Complete - Do not alter
void LabelList::print(std::ostream& ostr, const LabelType& label, char separator) const
{
    size_t level = this->getLabelIndex(label);
    MsgNode* n = this->heads_[level];
    while(nullptr != n)
    {
        ostr << n->msg_ << separator;
        n = n->next_[level];
    }
    ostr << std::endl;
}

// To be completed - must adhere to any requirements in the .h file
size_t LabelList::findLabelIndex(const LabelType& label) const
{
    for (size_t i = 0U; i < this->labels_.size(); i++)
    {
        if (this->labels_[i] == label)
        {
            return i;
        }
    }
    return INVALID_LABEL;
}

// Complete - Do not alter
size_t LabelList::getLabelIndex(const LabelType& label) const
{
    size_t retval = this->findLabelIndex(label);
    if(INVALID_LABEL == retval)
    {
        throw std::out_of_range("Label doesn't exist");
    }
    return retval;
}


