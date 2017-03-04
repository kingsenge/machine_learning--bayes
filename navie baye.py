class NaiveBaye:
    def __init__(self,wordlist):
        self.featureVectorLegal = {}
        self.featureVectorIllegal = {}

        for keyWord in wordlist:
            self.featureVectorLegal[keyWord] = 0
            self.featureVectorIllegal[keyWord] = 0

        self.featureLen = len(self.featureVectorIllegal)

        self.legalNum = 0
        self.illegalNum = 0

        self.y1 = 0
        self.y0 = 0

    def __calProbability__(self,option):
        if(option == 1):
            fVector = self.featureVectorLegal
            num = self.legalNum
        else:
            fVector = self.featureVectorIllegal
            num = self.illegalNum

        total =0
        for key,value in fVector.items():
                fVector[key] = (value + 1) / (num + self.featureLen)
                total += fVector[key]

    def loadTransSet(self,trainSet,option):
        if(option == 1):
            fVector = self.featureVectorLegal
            self.legalNum += len(trainSet)
            self.y1 +=1
        else:
            fVector = self.featureVectorIllegal
            self.illegalNum+= len(trainSet)
            self.y0 +=1

        for data in trainSet:
            fVector[data] +=1

    def calVectorPro(self):
        self.__calProbability__(1)
        self.__calProbability__(0)

    def getProbability(self,words):
        probabilityLegal = 1
        probabilityIllegal = 1

        y1 = self.y1/(self.y1+self.y0)
        y0 = 1 - y1

        for word  in words:
            probabilityLegal *= self.featureVectorLegal[word]
            probabilityIllegal*= self.featureVectorIllegal[word]

        probabilityLegal*=y1
        probabilityIllegal*=y0

        return probabilityLegal/(probabilityLegal+probabilityIllegal)

wordlist = ["select","customNo","sellNo","rentNo","from","where","amount",\
            "sharding","date","table","do","buy","book","sale","read"]

testNaiveBay = NaiveBaye(wordlist)

testNaiveBay.loadTransSet(["select","amount","from","table","where"],0)
testNaiveBay.loadTransSet(["customNo","sharding","buy","do","book","sale","amount","rentNo","sellNo","date"],1)
testNaiveBay.loadTransSet(["read","sharding","buy","do","book"],1)
testNaiveBay.loadTransSet(["rentNo","sellNo","buy","sharding","date"],1)
testNaiveBay.loadTransSet(["table","customNo","sale","do"],1)

testNaiveBay.calVectorPro()
#计算字符串合法的概率
result = testNaiveBay.getProbability(["select","date","do","table","amount","where","sharding"])
print(result)
