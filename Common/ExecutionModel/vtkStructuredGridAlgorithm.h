// SPDX-FileCopyrightText: Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
// SPDX-License-Identifier: BSD-3-Clause
/**
 * @class   vtkStructuredGridAlgorithm
 * @brief   Superclass for algorithms that produce only structured grid as output
 *
 *
 * vtkStructuredGridAlgorithm is a convenience class to make writing algorithms
 * easier. It is also designed to help transition old algorithms to the new
 * pipeline architecture. There are some assumptions and defaults made by this
 * class you should be aware of. This class defaults such that your filter
 * will have one input port and one output port. If that is not the case
 * simply change it with SetNumberOfInputPorts etc. See this classes
 * constructor for the default. This class also provides a FillInputPortInfo
 * method that by default says that all inputs will be StructuredGrid. If that
 * isn't the case then please override this method in your subclass.
 */

#ifndef vtkStructuredGridAlgorithm_h
#define vtkStructuredGridAlgorithm_h

#include "vtkAlgorithm.h"
#include "vtkCommonExecutionModelModule.h" // For export macro
#include "vtkStructuredGrid.h"             // makes things a bit easier

VTK_ABI_NAMESPACE_BEGIN
class vtkDataSet;
class vtkStructuredGrid;

class VTKCOMMONEXECUTIONMODEL_EXPORT vtkStructuredGridAlgorithm : public vtkAlgorithm
{
public:
  static vtkStructuredGridAlgorithm* New();
  vtkTypeMacro(vtkStructuredGridAlgorithm, vtkAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  ///@{
  /**
   * Get the output data object for a port on this algorithm.
   */
  vtkStructuredGrid* GetOutput();
  vtkStructuredGrid* GetOutput(int);
  virtual void SetOutput(vtkDataObject* d);
  ///@}

  /**
   * see vtkAlgorithm for details
   */
  vtkTypeBool ProcessRequest(
    vtkInformation*, vtkInformationVector**, vtkInformationVector*) override;

  // this method is not recommended for use, but lots of old style filters
  // use it
  vtkDataObject* GetInput();
  vtkDataObject* GetInput(int port);
  vtkStructuredGrid* GetStructuredGridInput(int port);

  ///@{
  /**
   * Assign a data object as input. Note that this method does not
   * establish a pipeline connection. Use SetInputConnection() to
   * setup a pipeline connection.
   */
  void SetInputData(vtkDataObject*);
  void SetInputData(int, vtkDataObject*);
  ///@}

  ///@{
  /**
   * Assign a data object as input. Note that this method does not
   * establish a pipeline connection. Use AddInputConnection() to
   * setup a pipeline connection.
   */
  void AddInputData(vtkDataObject*);
  void AddInputData(int, vtkDataObject*);
  ///@}

protected:
  vtkStructuredGridAlgorithm();
  ~vtkStructuredGridAlgorithm() override;

  // convenience method
  virtual int RequestInformation(vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector);

  /**
   * This is called by the superclass.
   * This is the method you should override.
   */
  virtual int RequestData(vtkInformation* request, vtkInformationVector** inputVector,
    vtkInformationVector* outputVector);

  ///@{
  /**
   * This is called by the superclass.
   * This is the method you should override.
   */
  virtual int RequestUpdateExtent(vtkInformation*, vtkInformationVector**, vtkInformationVector*)
  {
    return 1;
  };
  ///@}

  virtual int RequestUpdateTime(vtkInformation*, vtkInformationVector**, vtkInformationVector*)
  {
    return 1;
  };

  // see algorithm for more info
  int FillOutputPortInformation(int port, vtkInformation* info) override;
  int FillInputPortInformation(int port, vtkInformation* info) override;

private:
  vtkStructuredGridAlgorithm(const vtkStructuredGridAlgorithm&) = delete;
  void operator=(const vtkStructuredGridAlgorithm&) = delete;
};

VTK_ABI_NAMESPACE_END
#endif
