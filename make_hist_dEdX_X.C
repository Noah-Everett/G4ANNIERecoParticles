#include <vector>
#include <string>
using std::to_string;

struct step {
    double X;
    double dX;
    double E;
    double dE;
    double dEdX;
};

// double fitFct( double *x, double *par ) {
//     return par[0]+par[1]*x[0]+par[2]*x[0]*x[0];
// }

void make_hist_dEdX_X( vector< string > files )
{
    gROOT->ForceStyle();
    // gStyle->SetOptStat(0);

    TCanvas* canvas = new TCanvas( "c1", "", 1000, 1000 );
    // canvas->SetLogy();
    canvas->SetLogz();

    TChain* tree = new TChain( "dEdX;1" );
    for( string file : files )
        tree->Add( file.c_str() );
    
    vector< step > steps;
    step temp;

    // Used to determine hist limits
    double max_X = -1;
    double min_X = -1;
    double max_dEdX = -1;
    double min_dEdX = -1;

    tree->SetBranchAddress( "X", &temp.X );
    tree->SetBranchAddress( "dX", &temp.dX );
    tree->SetBranchAddress( "E", &temp.E );
    tree->SetBranchAddress( "dE", &temp.dE );
    tree->SetBranchAddress( "dEdX", &temp.dEdX );

    for( Int_t i = 0; i < tree->GetEntries(); i++ ) {
        tree->GetEntry( i );
        steps.push_back(temp);

        if( max_X == -1 ) {
            cout << temp.dEdX << endl;
            max_X = temp.X;
            min_X = temp.X;
            max_dEdX = temp.dEdX;
            max_dEdX = temp.dEdX;
        }

        if( max_X < temp.X ){ 
            max_X = temp.X;
            // cout << "max_X: " << i << " " << max_X << endl; 
        }
        if( min_X > temp.X ) min_X = temp.X;
        if( max_dEdX < temp.dEdX ){ 
            max_dEdX = temp.dEdX;
            cout << "max_dEdX: " << i << " " << max_dEdX << endl;
        }
        if( min_dEdX > temp.dEdX ){ 
            min_dEdX = temp.dEdX;
            // cout << "min_dEdX: " << i << " " << min_dEdX << endl;
        }
    } 

    // int nBins_GeV = 20; // number of bins per GeV
    // int nBins_x = ceil( max_Xv * nBins_GeV / 1000 ) - floor( min_Ev * nBins_GeV / 1000);

    cout << "max_dEdX: " << " " << max_dEdX << endl;
    cout << "min_dEdX: " << " " << min_dEdX << endl;
    cout << "max_X---: " << " " << max_X    << endl;
    cout << "max_X---: " << " " << max_X    << endl;

    double nBins_unitE = 100;
    double nBins_unitdEdX = 1;
    min_dEdX = -40;
    int nBins_x = ceil( max_X * nBins_unitE ) - floor( min_X * nBins_unitE );
    int nBins_y = ceil( max_dEdX * nBins_unitdEdX ) - floor( min_dEdX * nBins_unitdEdX );
    string xLabel = "Counts / " + to_string( int( ( ceil( max_X ) - floor( min_X ) ) / nBins_x ) ) + " MeV / " + to_string( ( ceil( max_dEdX ) - floor( min_dEdX ) ) / nBins_y ) + ";";
    
    cout << "TH2F* hist = new TH2F( \"\", \";\" \"E [MeV];\" \"dE/dX [MeV/cm];\" \"" + xLabel + "\", " << nBins_x << ", " << floor( min_X ) << ", " <<  ceil( max_X ) << ", " << nBins_y << ", " << floor( min_dEdX ) << ", " << ceil( max_dEdX ) << " );" << endl;

    // Total events
    TH2F* hist = new TH2F( "", ";" "X [m];" "dE/dX [MeV/m]"/*;" "Counts"*/, nBins_x, floor( min_X ), max_X /*ceil( max_X )*/, nBins_y, min_dEdX, max_dEdX );
    for( int i = 0; i < steps.size(); i++ ) hist->Fill( steps[ i ].X, steps[ i ].dEdX );

    // TF1* fitFct = new TF1( "fitFct","[0]+[1]*x+[2]*x*x+[3]*x*x*x+[4]*x*x*x*x+[5]*x*x*x*x*x+[6]*x*x*x*x*x*x",0,4);
    // TF1* fitFct = new TF1( "fitFct","[0]+[1]*sin([2]*x+[3])+[4]*sin([5]*x+[6])+[7]*sin([8]*x+[9])",0,4);
    // hist->Fit(fitFct);
    // fitFct->Draw("same");
    TF1* y0 = new TF1( "y0", "[0]*0", 0, 1e7 );
    hist->Fit(y0);
    y0->SetLineWidth(5);
    y0->Draw("same");
    hist->GetXaxis()->SetTitleOffset( 1.1 );
    hist->GetYaxis()->SetTitleOffset( 1.1  );
    hist->GetZaxis()->SetTitleOffset( 1.40  );
    canvas->SetRightMargin(0.12);


    
    // hist->SetLineColor( kBlack );
    // hist->SetLineWidth( 1 );
    // hist->SetFillColorAlpha( kGray+3   , 1.0 );
    
    // double scale = double( 5E12 ) / double( 1E18 * 500 );
    // double norm  = hist_tot->GetEntries() * scale;
    // cout << "Scale: " << scale << endl;

    // string label_tot = "Total Events in ANNIE"       ; label_tot += " (" + to_string( int( hist_tot->GetEntries() ) * scale ) + " events)";
    
    // cout << "Entries: hist_tot: " << setw( 6 ) << hist_tot->GetEntries() << " || Scaled Entries: hist_tot: " << hist_tot->GetEntries() * scale << endl;

    // TLegend* legend = new TLegend(0.442693,0.606316,0.863897,0.886216);
    // legend->AddEntry( hist_tot, label_tot.c_str() );
    // legend->SetBorderSize( 0 );

    // hist_tot->Scale( scale );

    // hist_tot->SetMaximum( 3E-03  );

    hist->Draw("COLZ");

    // legend->Draw( "Same" );

    // gPad->RedrawAxis();

    // canvas->SaveAs("dEdX.pdf");
}