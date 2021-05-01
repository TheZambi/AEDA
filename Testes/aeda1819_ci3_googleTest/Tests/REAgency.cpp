#include "REAgency.h"

REAgency::REAgency(): catalogItems(PropertyTypeItem("", "","", 0)) {
	//do nothing!
}

REAgency::REAgency(vector<Property*> properties): catalogItems(PropertyTypeItem("", "","", 0)) {
	this->properties = properties;
}

void REAgency::addProperty(Property* property) {
	this->properties.push_back(property);
}

void REAgency::addProperties(vector<Property*> properties) {
	this->properties = properties;
}

vector<Property*> REAgency::getProperties() const{
	return this->properties;
}

PropertyTypeItem REAgency::getTypeItem(string address, string postalCode, string typology) {
	PropertyTypeItem itemNotFound("", "", "", 0);
	BSTItrIn<PropertyTypeItem> it(catalogItems);
	while (!it.isAtEnd())
	{
		if( it.retrieve().getAddress() == address && it.retrieve().getPostalCode() == postalCode && it.retrieve().getTypology() == typology) {
			PropertyTypeItem pti(it.retrieve().getAddress(), it.retrieve().getPostalCode(), it.retrieve().getTypology(), 0);
			pti.setItems(it.retrieve().getItems());
			return pti;
		}
		it.advance();
	}
	return itemNotFound;
}

void REAgency::addTypeItem(Property* property) {
	PropertyTypeItem itemNotFound("", "","", 0);
	PropertyTypeItem pti(property->getAddress(), property->getPostalCode(), property->getTypology(), property->	getPrice());
	PropertyTypeItem ptiX = catalogItems.find(pti);
	if(ptiX == itemNotFound) {
		pti.addItems(property);
		this->catalogItems.insert(pti);
	}
	else {
		this->catalogItems.remove(ptiX);
		ptiX.addItems(property);
		this->catalogItems.insert(ptiX);
	}
	properties.push_back(property);
}

BST<PropertyTypeItem> REAgency::getTypeItems() const {
	return this->catalogItems;
}

vector<ClientRecord> REAgency::getClientRecords() const {
	vector<ClientRecord> records;
	HashTabClientRecord::const_iterator it1 = this->listingRecords.begin();
	HashTabClientRecord::const_iterator it2 = this->listingRecords.end();
	for(; it1 != it2; it1++) {
			records.push_back(*it1);
	}
	return records;
}

void REAgency::setClientRecords(vector<ClientRecord>& crs) {
	for(unsigned int i = 0; i < crs.size(); i++) {
		listingRecords.insert(crs[i]);
	}

}

priority_queue<Client> REAgency::getClientProfiles() const {
	return clientProfiles;
}
void REAgency::setClientProfiles(priority_queue<Client>& profiles) {
	clientProfiles = profiles;
}

//
// TODO: Part I   - BST
//
void REAgency::generateCatalog() {
	//TODO: A
    vector<Property*> toCat={properties[0]};
    int maxPrice=properties[0]->getPrice();
    for(size_t i=1;i<properties.size();i++)
    {
        if(toCat[0]->getAddress()!=properties[i]->getAddress()
        || toCat[0]->getPostalCode()!=properties[i]->getPostalCode()
        || toCat[0]->getTypology()!=properties[i]->getTypology())
        {
            PropertyTypeItem add(toCat[0]->getAddress(),toCat[0]->getPostalCode(),toCat[0]->getTypology(),maxPrice);
            add.setItems(toCat);
            catalogItems.insert(add);
            toCat={properties[i]};
            maxPrice=properties[i]->getPrice();
        }
        else
        {
            if(maxPrice<properties[i]->getPrice())
                maxPrice=properties[i]->getPrice();
            toCat.push_back(properties.at(i));
        }
    }
}

vector<Property*> REAgency::getAvailableProperties(Property* property) const {
	vector<Property*> temp;
	//TODO: B
    for(size_t i=0;i<properties.size();i++)
    {
        if(property->getTypology()==properties.at(i)->getTypology()
        &&property->getPostalCode()==properties.at(i)->getPostalCode()
        &&property->getAddress()==properties.at(i)->getAddress())
        {
            if(get<0>(properties.at(i)->getReservation())==NULL)
                temp.push_back(properties.at(i));
        }
    }
	return temp;
}

bool REAgency::reservePropertyFromCatalog(Property* property, Client* client, int percentage) {
	//TODO: C
    for(BSTItrIn<PropertyTypeItem> iter(catalogItems);!iter.isAtEnd(); iter.advance())
    {
        PropertyTypeItem aux=iter.retrieve();
        if(aux.getAddress()==property->getAddress() &&
            aux.getPostalCode()==property->getPostalCode()&&
            aux.getTypology()==property->getTypology())
        {
            for(size_t i=0;i<aux.getItems().size();i++)
            {
                if(get<0>(aux.getItems().at(i)->getReservation())==NULL)
                {
                    iter.retrieve().getItems().at(i)->setReservation({client,aux.getItems().at(i)->getPrice()*(100-percentage)/100});
                    client->addVisiting(property->getAddress(),property->getPostalCode(),property->getTypology(),to_string(aux.getItems().at(i)->getPrice()*(100-percentage)/100));
                    return true;
                }
            }
        }
    }
	return false;
}

//
// TODO: Part II  - Hash Table
//
void REAgency::addClientRecord(Client* client) {
	//TODO: D
	listingRecords.insert(client);

}

void REAgency::deleteClients() {
	//TODO: E
    auto iter=listingRecords.begin();
	while(iter!=listingRecords.end())
    {
	    if(iter->getClientPointer()->getVisitedProperties().size()==0 && get<0>(iter->getClientPointer()->getVisiting())=="")
	        iter = listingRecords.erase(iter);
	    else
	        iter++;
    }
}

//
// TODO: Part III - Priority Queue
//
void REAgency::addBestClientProfiles(const vector<Client>candidates, int min) {
	//TODO: F
    double counter=0.0;
	for(auto iter=candidates.begin();iter!=candidates.end();iter++)
    {
	    counter=0;
	    for(size_t i=0;i<properties.size();i++)
        {
	        if(get<0>(properties.at(i)->getReservation())->getEMail() == iter->getEMail())
	            counter++;
        }
	    cout << counter/iter->getVisitedProperties().size() << "     " << min << endl << endl;
	    if(counter/iter->getVisitedProperties().size()>min)
	        clientProfiles.push(*iter);
    }

}

vector<Property*> REAgency::suggestProperties() {
	//TODO: G
	vector<Property*> tempProperties;
    priority_queue<Client> aux;
    double diff=100000, closest;
    while(!clientProfiles.empty())
    {

        aux.push(clientProfiles.top());
        for(int i=0; i<properties.size();i++)
        {
            if(get<0>(properties.at(i)->getReservation())==NULL)
            {
                if(abs(stod(get<1>(clientProfiles.top().getVisiting()))-stod(properties.at(i)->getPostalCode()))<diff)
                {
                    if((get<0>(clientProfiles.top().getVisiting()) !=  properties.at(i)->getAddress() ||
                        get<1>(clientProfiles.top().getVisiting()) != properties.at(i)->getPostalCode() ||
                        get<2>(clientProfiles.top().getVisiting()) != properties.at(i)->getTypology() ||
                        get<3>(clientProfiles.top().getVisiting()) != to_string(properties.at(i)->getPrice()))){
                            diff = abs(stod(get<1>(clientProfiles.top().getVisiting())) - stod(properties.at(i)->getPostalCode()));
                            closest = i;
                    }
                }
            }

        }
        tempProperties.push_back(properties.at(closest));
        clientProfiles.pop();
    }
    clientProfiles=aux;
	return tempProperties;
}
