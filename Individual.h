#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

class Individual
{
private:
    string className;
    array<char, ATTR_SIZE> attributes;

public:
    Individual();
    Individual(string, array<char, ATTR_SIZE>);

    void print() const;
    string getClassName() const;
    array<char, ATTR_SIZE> getAttributes() const;

    bool classifyIndividual(vector<Individual>);
    bool classifyIndividual(map<string, map<char, array<double, ATTR_SIZE>>>, map<string, double>);
};

Individual::Individual()
{
    className = "undefined";
    attributes.fill('?');
}

Individual::Individual(string className, array<char, ATTR_SIZE> attributes)
{
    this->className = className;
    this->attributes = attributes;
}

bool Individual::classifyIndividual(vector<Individual> learn)
{
    int republicanCounter = 0;
    int democratCounter = 0;
    array<int, ATTR_SIZE> republicanAttrsCounters = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    array<int, ATTR_SIZE> democratAttrsCounters = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (auto &record : learn)
    {
        if (record.className == "republican")
        {
            republicanCounter++;
            for (int i = 0; i < ATTR_SIZE; ++i)
                if (this->attributes[i] == record.attributes[i])
                    republicanAttrsCounters[i]++;
        }
        else
        {
            democratCounter++;
            for (int i = 0; i < ATTR_SIZE; ++i)
                if (this->attributes[i] == record.attributes[i])
                    democratAttrsCounters[i]++;
        }
    }

    double probRepublican;
    double probDemocrat;

    array<double, ATTR_SIZE> probRepublicansAttrs;
    array<double, ATTR_SIZE> probDemocratsAttrs;

    int numberOfRecords = learn.size();

    probRepublican = (static_cast<double>(republicanCounter) / numberOfRecords);
    probDemocrat = (static_cast<double>(democratCounter) / numberOfRecords);

    for (int i = 0; i < ATTR_SIZE; ++i)
    {
        probRepublicansAttrs[i] = (static_cast<double>(republicanAttrsCounters[i]) / republicanCounter);
        probDemocratsAttrs[i] = (static_cast<double>(democratAttrsCounters[i]) / democratCounter);
    }

    double republican = probRepublican;
    double democrat = probDemocrat;
    for (int i = 0; i < ATTR_SIZE; ++i)
    {
        republican *= probRepublicansAttrs[i];
        democrat *= probDemocratsAttrs[i];
    }

    string classNamePrediction = (republican > democrat) ? "republican" : "democrat";
    return (classNamePrediction == this->className);
}

bool Individual::classifyIndividual(map<string, map<char, array<double, ATTR_SIZE>>> attrProbs, map<string, double> classNameProbs)
{
    double republican = classNameProbs["republican"];
    double democrat = classNameProbs["democrat"];

    for (int i = 0; i < ATTR_SIZE; ++i)
    {
        republican *= attrProbs["republican"][this->attributes[i]][i];
        democrat *= attrProbs["democrat"][this->attributes[i]][i];
    }

    string classNamePrediction = (republican > democrat) ? "republican" : "democrat";
    return (classNamePrediction == this->className);
}

string Individual::getClassName() const
{
    return this->className;
}

array<char, ATTR_SIZE> Individual::getAttributes() const
{
    return this->attributes;
}

void Individual::print() const
{
    cout << className << " ";
    for (auto &attr : attributes)
        cout << attr << " ";

    cout << endl;
}

#endif // INDIVIDUAL_H
