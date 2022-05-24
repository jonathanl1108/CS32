
void removeOdds(vector<int>& v)
{
    // call in the iterator
    vector<int>::iterator it;
    it = v.begin();
    while( it != v.end())
    {
        if( (*it) % 2)
        {
            v.erase(it);
            it--;
        }else
            it++;
    }
}

