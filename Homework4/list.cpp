void listAll(const Domain* d, string path) // two-parameter overload
{
    // relizing the pattern
    // if th node has child the order is [0] [1] ... and must not have any . attach
    // while if the node is a root of some sub tree then we have .+ root.lable();
    // base case
//    if( &(d->subdomains())==nullptr)
//        return;
    if(d->subdomains().empty() )
    {
        string finalLink=  d->label();
        cout<< finalLink;
        if(path == d->label())
            cout<<endl;
        return;
    }
    if( path != "")
        path = "."+path;
    
    // so its not empty then vist each
    for (vector<Domain*>::const_iterator it = d->subdomains().begin(); it != d->subdomains().end(); it++)
    {
        //
        string newPath=path;
        if(! (*it)->subdomains().empty())
        {
            newPath= (*it)->label()+path;
            listAll((*it),newPath);
            //cout<<newPath<<endl;
        }
        else
        {
            listAll((*it),newPath);
            cout<<newPath<<endl;
        }
       
    }
  
}

