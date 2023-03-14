#ifndef __IDM_PRICER_H
#define __IDM_PRICER_H

namespace idm
{
  class Pricer
  {
    protected:
      std::shared_ptr<Contract> mContract;

    public:
      Pricer(std::shared_ptr<Contract> contract)
        :mContract{contract}
      {}

      virtual double price() const = 0;
      virtual ~Pricer() {}
  };
}

#endif // __IDM_PRICER_H
